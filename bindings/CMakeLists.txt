cmake_minimum_required(VERSION 3.2...4.1.2)
project(mathpp_bindings)

# using cpp 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# get the package finder
include(FetchContent)

# get pybind11
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v3.0.1
)

FetchContent_MakeAvailable(pybind11)

# define the target and link with math++ lib
pybind11_add_module(mathpy python.cpp)
target_link_libraries(mathpy PRIVATE mathpp)

install(TARGETS mathpy LIBRARY DESTINATION . ARCHIVE DESTINATION . RUNTIME DESTINATION .)