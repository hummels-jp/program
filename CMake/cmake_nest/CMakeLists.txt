# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Project name and version
project(cmake_nest VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIBPATH, ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECPATH, ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(HEADPATH, ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CALCULATORLIB, calculator)
set(SORTLIB, sort)

set(EXENAME1, calculator)
set(EXENAME2, sort)

add_subdirectory(calculator)
add_subdirectory(sort)
add_subdirectory(calculator_test)
add_subdirectory(sort_test)
