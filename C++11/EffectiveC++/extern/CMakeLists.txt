cmake_minimum_required(VERSION 3.10)
project(ExternExample)

set(CMAKE_CXX_STANDARD 11)

# Add the executable
add_executable(ExternExample main.cpp global.cpp)