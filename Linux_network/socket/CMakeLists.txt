# 最低CMake版本
cmake_minimum_required(VERSION 3.10)

# 项目名
project(SocketExample)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 生成服务器可执行文件
add_executable(socket_server socket_server.cpp)

# 生成客户端可执行文件
add_executable(socket_client socket_client.cpp)
