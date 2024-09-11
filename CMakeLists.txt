cmake_minimum_required(VERSION 3.10)
project(XC64)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -flto -funroll-loops -ftree-vectorize -fomit-frame-pointer")

# Include directories relative to the source directory
include_directories(${PROJECT_SOURCE_DIR}/src)

# Add only the specified source files
add_executable(XC64
    src/library_loader.cpp
    src/
)