cmake_minimum_required(VERSION 3.10)
project(MySystemVMessageQueue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(message_queue_server message_queue_server.cpp)
add_executable(message_queue_client message_queue_client.cpp)
