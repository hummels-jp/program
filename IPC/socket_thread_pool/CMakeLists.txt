cmake_minimum_required(VERSION 3.10)
project(SocketThreadPool)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(server pthread)
target_link_libraries(client pthread)
