# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(MySocketExample)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executables if source files exist
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/my_socket_server.cpp")
	add_executable(my_socket_server my_socket_server.cpp)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/my_socket_client.cpp")
	add_executable(my_socket_client my_socket_client.cpp)
endif()
