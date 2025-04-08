cmake_minimum_required(VERSION 3.10)

# Set the project name
project(calculator_test)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get the list of source files
aux_source_directory(. SRC_LIST)
include_directories(${HEADPATH})
link_directories(${LIBPATH})
link_libraries(${CALCULATORLIB})
set(EXECUTABLE_OUTPUT_PATH ${EXECPATH})
add_executable(${EXENAME1} ${SRC_LIST})
