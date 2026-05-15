/**
 * \file input_parser_tests.cpp
 * \author Dylan Shah (code@dylan-shah.com)
 * \brief Tests the input parser
 * \version 0.1
 * \date 2026-05-14
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

#include "input_parser.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Check inputs come out correctly", "[DayOne][Parser]") {
    int correct_vals[] = { -68, -30, 48, -5, 60, -55, -1, -99, 14, -82 };

    std::filesystem::path tempDir  = std::filesystem::temp_directory_path();
    std::filesystem::path tempFile = tempDir / "AVC.2025.1.Test.tmp";

    std::ofstream file(tempFile);
    file << "L68\n"
            "L30\n"
            "R48\n"
            "L5\n"
            "R60\n"
            "L55\n"
            "L1\n"
            "L99\n"
            "R14\n"
            "L82\n";
    file.close();

    auto parser = input_parser<int>(tempFile).begin();
    for (auto i : correct_vals) {
        CHECK(*parser++ == i);
    }
    std::remove(tempFile.c_str());
}
