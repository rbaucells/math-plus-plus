cmake_minimum_required(VERSION 3.12)
project(mathpp)

# using cpp 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MATHPP_BUILD_TESTS "Build tests" ON)
option(MATHPP_BINDINGS "Build Python bindings" ON)

add_library(mathpp INTERFACE
        src/exceptions.h
        src/expression.h
        src/helper.h
        src/vector/exceptions.h
        src/vector/sparse/vector.h
        src/vector/sparse/helper.h
        src/vector/dense/vector.h
        src/vector/dense/helper.h
        src/matrix/exceptions.h
        src/matrix/sparse/matrix.h
        src/matrix/sparse/helper.h
        src/vector/dense/operators/compare.h
        src/vector/sparse/operators/compare.h
        src/matrix/sparse/operators/compare.h
        src/matrix/dense/operators/add.h
        src/matrix/dense/operators/compare.h
        src/matrix/dense/operators/multiply.h
        src/matrix/dense/operators/subtract.h
        src/matrix/dense/helper.h
        src/telemetry.h
        src/matrix/dense/matrix.h)

target_include_directories(mathpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MATHPP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(MATHPP_BINDINGS)
    add_subdirectory(bindings)
endif()