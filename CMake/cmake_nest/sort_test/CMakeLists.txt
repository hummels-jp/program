cmake_minimum_required(VERSION 3.10)

# Set the project name
project(sort)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get the list of source files
aux_source_directory(. SRC_LIST)
include_directories(${HEADPATH})
link_directories(${LIBPATH})
link_libraries(${SORTLIB})
set(EXECUTABLE_OUTPUT_PATH ${EXECPATH})
# Ensure EXENAME2 is set to a valid target name
set(EXENAME2 sort_test)
add_executable(${EXENAME2} ${SRC_LIST})
