cmake_minimum_required(VERSION 3.12)
project(mathpp)

# using cpp 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MATHPP_BUILD_TESTS "Build tests" ON)
option(MATHPP_BINDINGS "Build Python bindings" ON)

# math++ header only lib
add_library(mathpp INTERFACE
        src/matrix/dense/matrix.h)

# make include folder publicly available
target_include_directories(mathpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MATHPP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(MATHPP_BINDINGS)
    add_subdirectory(bindings)
endif()
