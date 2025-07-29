cmake_minimum_required(VERSION 3.10)
project(pimpl_example)

set(CMAKE_CXX_STANDARD 11)

add_executable(pimpl_example
    main.cpp
    pimpl.cpp
)