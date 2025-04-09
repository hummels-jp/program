cmake_minimum_required(VERSION 3.10)

# Project name
project(Thread_Demo)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# Add executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
# Link pthread library
target_link_libraries(${PROJECT_NAME} pthread)
