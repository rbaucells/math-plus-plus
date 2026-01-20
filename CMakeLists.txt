cmake_minimum_required(VERSION 3.12)
project(math++)

# using cpp 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
add_subdirectory(tests)

# math++ lib
add_library(math++ STATIC
        src/curve.cpp
)

# make include folder publicly available
target_include_directories(math++ PUBLIC include)