cmake_minimum_required(VERSION 3.23)
set(name "2025.1")

add_executable(${name})
target_sources(${name}
  PRIVATE
    main.cpp
)
target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(${name} PUBLIC cxx_std_20)

if(BUILD_TEST)
  find_package(Catch2 REQUIRED)

  add_executable("${name}_Tests")
  target_sources("${name}_Tests"
    PRIVATE
      lock_test.cpp
  )
  target_include_directories(${name}_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
  target_compile_features(${name}_Tests PUBLIC cxx_std_20)
  target_link_libraries("${name}_Tests" PRIVATE Catch2::Catch2WithMain)

  add_dependencies(build_and_test_prog "${name}_Tests")

  # Register this test target globally so the root can pick it up
  set_property(GLOBAL APPEND PROPERTY REGISTERED_TESTS "${name}_Tests")
endif()

