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

/**
 * \brief The actual iterator for the file
 *
 * @tparam T
 */
template<std::signed_integral T>
struct input_parser<T>::itor {
    using value_type        = T;
    using iterator_category = std::input_iterator_tag;
    using difference_type   = std::ptrdiff_t;

    itor() noexcept
        : file_ptr(nullptr) {}

    explicit itor(std::shared_ptr<std::ifstream> f)
        : file_ptr(f) {
        ++(*this);
    }

    value_type operator*() const { return current; }

    itor& operator++() {
        if (!file_ptr || !(*file_ptr)) {
            file_ptr.reset();
            return *this;
        }

        std::string line;
        if (!std::getline(*file_ptr, line)) {
            file_ptr.reset();
            return *this;
        }

        std::istringstream iss{ line };
        value_type         output = 0;
        char               c{};
        iss >> c;
        iss >> output;
        if (c == 'L') output *= -1;
        current = output;
        return *this;
    }

    itor operator++(int) {
        itor tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const itor& o) const { return file_ptr == o.file_ptr; }

    bool operator!=(const itor& o) const { return !(*this == o); }

  private:
    std::shared_ptr<std::ifstream> file_ptr;
    value_type                     current{};
};

static_assert(std::input_iterator<input_parser<int>::itor>,
              "Iterator is not correct");
