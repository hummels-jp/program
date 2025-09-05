cmake_minimum_required(VERSION 3.10)
project(SharedMemoryIPC)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(shared_memory_sender shared_memory_sender.cpp)
add_executable(shared_memory_receiver shared_memory_receiver.cpp)
