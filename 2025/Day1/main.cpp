/**
 * \file main.cpp
 * \author Dylan Shah (code@dylan-shah.com)
 * \brief My Day One Solution
 * \ref https://adventofcode.com/2025/day/1 "Problem"
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

#include "input_parser.hpp"
#include "lock.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>

int main(int argc, char const* argv[]) {
    // CMD line parcing
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [inputs]\n";

        std::exit(1);
    }
    if (not std::filesystem::exists(argv[1])) {
        std::cerr << "Inputs must be a valid file path";

        std::exit(1);
    }
    histogram_lock<99> lock{ 50 };
    input_parser<int>  inputs{ argv[1] };
    for (auto input : inputs)
        lock += input;

    std::cout << "Number of times lock was at 0: " << lock.get_frequency(0);

    return 0;
}
