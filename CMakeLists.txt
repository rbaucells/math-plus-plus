cmake_minimum_required(VERSION 3.12)
project(math++)

# using cpp 20
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)

# math++ lib
add_library(math++ STATIC src/curve.cpp src/vector2.cpp src/vector3.cpp src/vector4.cpp)

# make include folder publicly available
target_include_directories(math++ PUBLIC include)