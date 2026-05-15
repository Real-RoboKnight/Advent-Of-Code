/**
 * \file input_parser.hpp
 * \author Dylan Shah (code@dylan-shah.com)
 * \brief Functions to parse the input of the file, converting them to signed
 * integers.
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

#pragma once
#include <filesystem>
#include <fstream>
#include <memory>

/**
 * \brief An iterator that goes converts file to signed integers
 * \tparam T Type of integral that the iterator will generate
 */
template<std::signed_integral T>
class input_parser {
  public:
    struct itor;

    input_parser(std::filesystem::path path)
        : file_ptr(std::make_shared<std::ifstream>(path)) {}

    itor begin() { return itor(file_ptr); }

    itor end() { return itor(); }

  private:
    std::shared_ptr<std::ifstream> file_ptr;
};

#include "input_parser.hxx"
