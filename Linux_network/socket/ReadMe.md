# Socket 通信示例使用说明

本目录包含基于 C++ 的 TCP socket 通信示例，包括服务器（socket_server）和客户端（socket_client）。

## 编译方法

1. 进入本目录：
	```bash
	cd /home/kotei/huqianqian/git_project/program/Linux_network/socket
	```
2. 创建并进入 build 目录：
	```bash
	mkdir -p build && cd build
	```
3. 运行 CMake 并编译：
	```bash
	cmake ..
	make
	```
4. 编译完成后会生成 `socket_server` 和 `socket_client` 可执行文件。

## 运行方法

### 1. 启动服务器
在 build 目录下运行：
```bash
./socket_server
```
服务器会监听本地 8888 端口，等待客户端连接。

### 2. 启动客户端
另开一个终端，进入 build 目录，运行：
```bash
./socket_client
```
客户端会连接本地 8888 端口，发送消息并接收服务器回显。

## 注意事项
- 服务器和客户端默认使用 127.0.0.1（本地回环地址）和 8888 端口。
- 如需更改端口或 IP，请修改源码后重新编译。
- 运行时请确保端口未被其他程序占用。

## 文件说明
- `socket_server.cpp`：TCP 服务器端示例代码
- `socket_client.cpp`：TCP 客户端示例代码
- `CMakeLists.txt`：CMake 构建配置文件
