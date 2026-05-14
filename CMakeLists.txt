cmake_minimum_required(VERSION 3.23)
project(Advent_Of_Code)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Create CompileCommands.json for clang tools" ON)

option(BUILD_TEST "Build the test executable" ON)
include(CMakeDependentOption)
cmake_dependent_option(RUN_TEST "Run tests on build. If set to OFF, tests can be run from ${CMAKE_BINARY_DIR}/Tests/tests" ON BUILD_TEST OFF)

add_custom_target(build_and_test_prog ALL)
add_subdirectory(2025/Day1)

if(RUN_TEST AND BUILD_TEST)
  get_property(test_targets GLOBAL PROPERTY REGISTERED_TESTS)
  foreach(t IN LISTS test_targets)
    add_custom_command(TARGET build_and_test_prog
      POST_BUILD
      COMMAND echo "--- Running ${t} ---"
      COMMAND $<TARGET_FILE:${t}> -d yes -v high --colour-mode ansi
      VERBATIM
    )
  endforeach()
endif()