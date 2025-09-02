# Default to g++ compiler (modify to actual path if needed)
set(CMAKE_C_COMPILER "gcc" CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "g++" CACHE STRING "" FORCE)
cmake_minimum_required(VERSION 3.10)
project(PolygonOverlap)

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCES
    main.cpp
    Polygon.cpp
    PolygonFilter.cpp
    Point.cpp
)

# Add header file directories (including include directory containing json.hpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PolygonOverlap ${SOURCES})

# Link pthread library
target_link_libraries(PolygonOverlap pthread)