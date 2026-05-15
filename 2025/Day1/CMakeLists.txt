cmake_minimum_required(VERSION 3.23)
set(name "Secret_Entrance")

add_executable(${name})
target_sources(${name}
  PRIVATE
    main.cpp
)
target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(${name} PUBLIC cxx_std_20)
if(MSVC)
  target_compile_options(${name} PRIVATE /W4 /WX)
else()
  target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic -Wformat=2 -Wconversion -Wshadow -Wfloat-equal -Wundef )
endif()
if(BUILD_TEST)
  add_executable("${name}_Tests")
  target_sources("${name}_Tests"
    PRIVATE
      lock_test.cpp
      input_parser_tests.cpp
  )
  target_include_directories(${name}_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
  target_compile_features(${name}_Tests PUBLIC cxx_std_20)
  target_link_libraries("${name}_Tests" PRIVATE Catch2::Catch2WithMain)
  if(MSVC)
    target_compile_options("${name}_Tests" PRIVATE /W4 /WX)
  else()
    target_compile_options("${name}_Tests" PRIVATE -Wall -Wextra -Wpedantic -Wformat=2 -Wconversion -Wshadow -Wfloat-equal -Wundef )
  endif()

  add_test(NAME day1_tests COMMAND $<TARGET_FILE:${name}_Tests>)
  add_dependencies(build_and_test_prog "${name}_Tests")

  # Register this test target globally so the root can pick it up
  set_property(GLOBAL APPEND PROPERTY REGISTERED_TESTS "${name}_Tests")
endif()

