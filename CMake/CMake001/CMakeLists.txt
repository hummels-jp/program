# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(CMake001)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Add header files (if needed)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Add executable
add_executable(CMakeTest001 ${SOURCES})



# Include directories (if needed)
# target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link libraries (if needed)
# target_link_libraries(${PROJECT_NAME} PRIVATE some_library)