cmake_minimum_required(VERSION 3.10)

# Set the project name
project(calculator)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get the list of source files
aux_source_directory(. SRC_LIST)
# message(STATUS "Source files: ${SRC_LIST}")
# Include the directory for header files
include_directories(${HEADPATH})

set(LIBRARY_OUTPUT_PATH ${LIBPATH})
# Add the executable
# Add the library
add_library(${CALCULATORLIB} STATIC ${SRC_LIST})
