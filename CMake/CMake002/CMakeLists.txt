# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(CMake002)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    main.cpp
)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})