# My solutions to the Advent Of Code problems.

[Link to the Advent Of Code](https://adventofcode.com/)

If you are also doing the problems, I encourage you to solve them independently to grow your own skills. Please do not use my solutions to cheat yourself of learning.

If you need to contact me, you can [email me](mailto:code@dylan-shah.com?subject=Advent%20Of%20Code).

# Dependencies
 - C++ 20
 - Cmake - Build System
 - Catch2 - Testing framework (Cmake will auto-install)

## Build Project
Run: `cmake --preset Development -B build/` once from the project root to initialize the build system. See the Cmake documentation if this does not work.

Run `cmake --build build/` to build the project. The first build will be long, but subsequent builds should be faster.

Final executables will be in `build/<year>/Day<day>/`

## License 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

A copy of the license can be found here: \ref License.md
