cmake_minimum_required(VERSION 3.10)
project(MyNamedPipe)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/named_pipe_server.cpp")
    add_executable(my_named_pipe_server named_pipe_server.cpp)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/named_pipe_client.cpp")
    add_executable(my_named_pipe_client named_pipe_client.cpp)
endif()
