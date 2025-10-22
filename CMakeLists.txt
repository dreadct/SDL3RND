cmake_minimum_required(VERSION 3.25)

project(SDL3RND)

# Include Conan's generated toolchain file
include(${PROJECT_SOURCE_DIR}/build/conan_toolchain.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project dirs
set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src/app)
