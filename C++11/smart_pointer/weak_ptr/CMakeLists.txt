cmake_minimum_required(VERSION 3.10)
project(weak_ptr_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(weak_ptr_demo
    weak_ptr.cpp
    ClassA.cpp
    ClassB.cpp
)