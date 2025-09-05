cmake_minimum_required(VERSION 3.10)
project(MyMemoryMapping)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(memory_mapping_server memory_mapping_server.cpp)
add_executable(memory_mapping_client memory_mapping_client.cpp)
