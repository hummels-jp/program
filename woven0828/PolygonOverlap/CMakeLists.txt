cmake_minimum_required(VERSION 3.10)
project(PolygonOverlap)

set(CMAKE_CXX_STANDARD 11)

# 添加源文件
set(SOURCES
    main.cpp
    Polygon.cpp
    PolygonFilter.cpp
    Point.cpp
)

# 添加头文件目录（包含 json.hpp 所在的 include 目录）
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PolygonOverlap ${SOURCES})