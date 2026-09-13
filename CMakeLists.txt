cmake_minimum_required(VERSION 3.20)

project(
    LimitOrderBook
    VERSION 1.0
    DESCRIPTION "Low Latency C++ Limit Order Book and Matching Engine"
    LANGUAGES CXX
)
# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler Warnings
if(MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-WALL -Wextra -Wpedantic)
endif()

# Build the source code
add_subdirectory(src)

# Testing
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)