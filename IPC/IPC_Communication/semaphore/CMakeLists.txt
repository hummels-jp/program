cmake_minimum_required(VERSION 3.10)
project(SystemVSemaphore)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(semaphore_server semaphore_server.cpp)
add_executable(semaphore_client semaphore_client.cpp)
