/**
 * \file lock.hpp
 * \author Dylan Shah (code@dylan-shah.com)
 * \brief Implements a lock that holds a histogram of values.
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
#pragma once
#include <array>
#include <concepts>
#include <format>

/**
 * \brief A lock that keeps a histogram of how frequently each value is present
 *
 * \todo refactor the histogram into another class, and have it a separate
 * dependency from the lock
 *
 * @tparam max_elem The largest value on the lock
 * @tparam min_elem The smallest value on the lock
 * @tparam T The type of the values on the lock
 */
template<std::size_t          max_elem,
         std::size_t          min_elem = 0,
         std::signed_integral T        = int>
    requires(max_elem > min_elem)
class histogram_lock {
  public:
    /**
     * \brief Construct a new lock object at position init
     *
     * \param init Value that the lock starts at
     */
    histogram_lock(T init) { set_current_value(init); }

    /**
     * \brief sets the current position of the lock
     *
     * \param val New position
     * \throws std::range_error Value not between min and max
     */
    void set_current_value(T val) {
        bounds_check(val);
        current_value = std::move(val);
        histogram[val - min]++;
    }

    /**
     * \brief Sets the current position of the lock
     *
     * \param val New position
     * \throws std::range_error Value not between min and max
     */
    void operator==(T val) { set_current_value(val); }

    /**
     * \brief Increases the position of the lock by \ref val "val" amount
     *
     * \param val Delta
     * \throws std::range_error Value not between min and max
     */

    void operator+=(T val) {
        // Add val to current_value, then wrap and set
        set_current_value(wrap_to_range(current_value + val));
    }

    /**
     * \brief Decreases the position of the lock by \ref val "val" amount
     *
     * \param val Delta
     * \throws std::range_error Value not between min and max
     */
    void operator-=(T val) { this->operator+=(-val); }

    /**
     * \brief Get the current value object
     */
    const T get_current_value() const { return current_value; }

    /**
     * \brief Gets how many times the lock was at val
     *
     * \param val
     * \return count
     */
    T get_frequency(T val) {
        bounds_check(val);
        return histogram[val - min];
    }

  private:
    static constexpr T min   = static_cast<T>(min_elem);
    static constexpr T max   = static_cast<T>(max_elem);
    static constexpr T range = max - min + 1;

    std::array<T, max - min + 1> histogram{};
    T                            current_value;

    /**
     * \brief Checks if the argument is in the range that this lock can handle
     *
     * Throws if out of bounds or returns true (can not return false).
     * \param t checked value
     * \return true
     * \throws std::range_error value not in range
     */
    bool bounds_check(T t) {
        if (t > max || t < min)
            throw std::range_error{ std::format(
                "Value {} not in lock bounds [{} - {}]", t, min, max) };
        return true;
    }

    /**
     * \brief Does the modular wraping math.
     */
    static constexpr T wrap_to_range(T val) {
        if (val >= min && val <= max) [[likely]]
            return val;
        return min + ((val - min) % range + range) % range;
    }
};
