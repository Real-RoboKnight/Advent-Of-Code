/**
 * \file lock_test.cpp
 * \author Dylan Shah (code@dylan-shah.com)
 * \brief Tests the lock to see if it works as expected
 * \version 0.1
 * \date 2026-05-13
 *
 * \copyright Copyright (c) 2026
 *
 * \parblock License:
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * \endparblock
 *
 */
#include "lock.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <stdexcept>

TEST_CASE("Ensure that Lock can be created with any integral type",
          "[DayOne][Lock][Template]") {
    histogram_lock<10, 0, int>{ 0 };
    histogram_lock<100, 0, char>{ 0 };
    histogram_lock<10, 0, long long>{ 0 };
    // histogram_lock<10, 0, std::uint8_t>{ 0 }; //Not signed
    histogram_lock<10, 0, std::int_least16_t>{ 0 };
}

TEST_CASE("Ensure that the lock can be rotated, and the count is correct",
          "[DayOne][Lock][Use]") {
    histogram_lock<100> lock{ 50 };
    REQUIRE(lock.get_current_value() == 50);
    REQUIRE(lock.get_frequency(0) == 0);
    REQUIRE(lock.get_frequency(50) == 1);
    lock += 5;
    lock -= 10;
    lock += 5;
    REQUIRE(lock.get_current_value() == 50);
    REQUIRE(lock.get_frequency(50) == 2);
    REQUIRE(lock.get_frequency(55) == 1);
    REQUIRE(lock.get_frequency(45) == 1);
}

TEST_CASE("Ensure that the the lock can roll around max value",
          "[DayOne][Lock][Overflow]") {
    histogram_lock<99> lock{ 50 };
    REQUIRE_NOTHROW(lock += 120);
    REQUIRE_NOTHROW(lock -= 120);
    REQUIRE_THROWS_AS(lock.set_current_value(150), std::range_error);
    GIVEN("Lock at 50") {
        lock.set_current_value(50);
        std::cout << "After reset: " << lock.get_current_value() << "\n";
        WHEN("Incremented by 60") {
            lock += 60;
            THEN("Lock should be 10") {
                REQUIRE(lock.get_current_value() == 10);
                REQUIRE(lock.get_frequency(10) == 1);
            }
        }
        WHEN("Decremented by 60") {
            lock -= 60;
            THEN("Lock should be 90") {
                REQUIRE(lock.get_current_value() == 90);
                REQUIRE(lock.get_frequency(90) == 1);
            }
        }
        WHEN("Incremented by 160") {
            lock += 160;
            THEN("Lock should be 10") {
                REQUIRE(lock.get_current_value() == 10);
                REQUIRE(lock.get_frequency(10) == 1);
            }
        }
        WHEN("Decremented by 160") {
            lock -= 160;
            THEN("Lock should be 90") {
                REQUIRE(lock.get_current_value() == 90);
                REQUIRE(lock.get_frequency(90) == 1);
            }
        }
    }
}
