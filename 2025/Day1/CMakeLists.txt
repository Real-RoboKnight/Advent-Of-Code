cmake_minimum_required(VERSION 3.23)
set(name "Day_One")
add_executable(${name})
target_sources(${name}
  PRIVATE
    main.cpp
)
target_compile_features(${name} PUBLIC cxx_std_20)