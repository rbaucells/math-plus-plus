cmake_minimum_required(VERSION 3.12)
project(math-tests)

# using cpp 20
set(CMAKE_CXX_STANDARD 20)

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
add_executable(math-tests
        main.cpp
        matrix.test.cpp
        vector.test.cpp
)

# link with the math lib
target_link_libraries(math-tests PRIVATE math++ GTest::gtest_main)

# enable more warnings in tests for better
target_compile_options(math-tests PRIVATE -Wall -Wextra -Wpedantic)

# auto-discover Gtests as Ctests
include(GoogleTest)
gtest_discover_tests(math-tests)