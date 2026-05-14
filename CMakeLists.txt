cmake_minimum_required(VERSION 3.23)
project(Advent_Of_Code)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Create CompileCommands.json for clang tools" ON)

option(BUILD_TEST "Build the test executable" ON)
include(CMakeDependentOption)
cmake_dependent_option(AUTO_RUN_TEST "Run tests on build. If set to OFF, tests can be run from ctest --test-dir ${CMAKE_BINARY_DIR} --output-on-failure" ON BUILD_TEST OFF)
if(BUILD_TEST) # Fetch cmake from github
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.6.0 # or latest stable version
  )
  FetchContent_MakeAvailable(Catch2)
  include(CTest)
  enable_testing()
endif()

add_custom_target(build_and_test_prog ALL)
add_subdirectory(2025/Day1)

if(AUTO_RUN_TEST AND BUILD_TEST)
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