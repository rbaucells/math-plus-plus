cmake_minimum_required(VERSION 3.12)
project(mathpp CXX)

# thing to get things through git
include(FetchContent)

# c++ 23
set(CMAKE_CXX_STANDARD 23)
# enforce the c++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# disable compiler specific things
set(CMAKE_CXX_EXTENSIONS OFF)

# settings
option(MATHPP_BUILD_TESTS "Build tests" ON)
option(MATHPP_BUILD_BENCHMARKS "Build benchmarks" ON)
option(MATHPP_PYTHON_BINDINGS "Build python bindings" ON)

# find all impl headers
file(GLOB_RECURSE IMPL_HEADERS "mathpp/implementation/*.h")

# header only library
add_library(mathpp INTERFACE ${IMPL_HEADERS})

# so people who include see the includes
target_include_directories(mathpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# testing
if (MATHPP_BUILD_TESTS)
    enable_testing()

    # get gtest
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.17.0
    )

    # make it available
    FetchContent_MakeAvailable(googletest)

    # get all test source files
    file(GLOB_RECURSE TEST_SRCS "tests/cpp/*.cpp")

    # define gtest executable
    add_executable(mathpp-tests ${TEST_SRCS})

    # link with GTEST and mathpp
    target_link_libraries(mathpp-tests PRIVATE mathpp GTest::gtest_main)

    # turn on telemetry
    target_compile_definitions(mathpp-tests PRIVATE MATHPP_ENABLE_TELEMETRY)

    # enable more warnings in tests for better
    target_compile_options(mathpp-tests PRIVATE -Wall -Wextra -Wpedantic)
endif ()

# benchmarks
if (MATHPP_BUILD_BENCHMARKS)
    # get google benchmarks
    FetchContent_Declare(
            googlebenchmark
            GIT_REPOSITORY https://github.com/google/benchmark.git
            GIT_TAG v1.9.5
    )

    # make it available
    FetchContent_MakeAvailable(googlebenchmark)

    # find all benchmark source files
    file(GLOB_RECURSE BENCHMARK_SRCS "benchmarks/*.cpp")

    # define benchmark executable
    add_executable(mathpp-benchmarks ${BENCHMARK_SRCS})

    # link with google benchmarks and mathpp
    target_link_libraries(mathpp-benchmarks PRIVATE mathpp benchmark::benchmark_main)
endif ()

# python bindings
if (MATHPP_PYTHON_BINDINGS)
    # find pybind11
    FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11.git
            GIT_TAG v3.0.4
    )

    # make it available
    FetchContent_MakeAvailable(pybind11)

    # make sure python 3 is installed
    find_package(Python 3 COMPONENTS Interpreter Development REQUIRED)

    # find all py bindings source files
    file(GLOB_RECURSE PYTHON_BINDINGS_SRCS "bindings/python/*.cpp")

    # add py module
    pybind11_add_module(mathpy MODULE ${PYTHON_BINDINGS_SRCS} bindings/python/main.h)

    # link with mathpp
    target_link_libraries(mathpy PRIVATE mathpp)

    # packaging stuff
    set(MATHPY_STAGING_DIR "${CMAKE_CURRENT_BINARY_DIR}/wheel_staging")
    set(MATHPY_MODULE_DIR "${MATHPY_STAGING_DIR}/mathpy")

    add_custom_target(mathpy-package
            # delete old stuff
            COMMAND ${Python_EXECUTABLE} -c "import shutil; shutil.rmtree(r'${MATHPY_STAGING_DIR}', ignore_errors=True)"
            # make module directory
            COMMAND ${CMAKE_COMMAND} -E make_directory "${MATHPY_MODULE_DIR}"

            # copy .so bindings into staging module folder
            COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:mathpy>" "${MATHPY_MODULE_DIR}/"

            COMMAND ${Python_EXECUTABLE} -c "with open(r'${MATHPY_MODULE_DIR}/__init__.py', 'w') as f: f.write('from .mathpy import *\\n')"

            # generate stubs into staging folder
            COMMAND ${Python_EXECUTABLE} -m pybind11_stubgen mathpy
            --output-dir "${MATHPY_MODULE_DIR}"

            # write into staging dir a pyproject.toml
            COMMAND ${Python_EXECUTABLE} -c "with open(r'${CMAKE_SOURCE_DIR}/bindings/python/pyproject.toml', 'r') as i, open(r'${MATHPY_STAGING_DIR}/pyproject.toml', 'w') as o: o.write(i.read())"

            # build the wheel from pyproject.toml
            COMMAND ${Python_EXECUTABLE} -m build --wheel "${MATHPY_STAGING_DIR}"

            # dont do this stuff until mathpy is alr built
            DEPENDS mathpy
            COMMENT "Generating stubbs and packaging mathpy wheel..."
            VERBATIM
    )
endif ()

# other bindings (etc.)
