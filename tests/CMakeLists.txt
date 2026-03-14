cmake_minimum_required(VERSION 3.12)
project(mathpp-tests)

# using cpp 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include package that lets us get things from git
include(FetchContent)

# get google test from git
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

# make it available for use in this CMakeLists.txt
FetchContent_MakeAvailable(googletest)

# math-tests executable
add_executable(mathpp-tests main.cpp
        helper.tests.cpp
        vector/dense/helper.tests.cpp
        vector/sparse/helper.tests.cpp
        matrix/dense/helper.tests.cpp
        matrix/sparse/helper.tests.cpp
        vector/dense/vector.tests.cpp
        matrix/dense/matrix.tests.cpp
        vector/sparse/vector.tests.cpp
        matrix/sparse/matrix.tests.cpp
        matrix/dense/operators/compare.tests.cpp
        vector/dense/operators/compare.tests.cpp
        vector/sparse/operators/compare.tests.cpp
)

# link with the math lib
target_link_libraries(mathpp-tests PRIVATE mathpp GTest::gtest_main)

# enable more warnings in tests for better
target_compile_options(mathpp-tests PRIVATE -Wall -Wextra -Wpedantic)

# auto-discover Gtests as Ctests
include(GoogleTest)
gtest_discover_tests(mathpp-tests)