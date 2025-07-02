#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "socket creation failed\n";
        return 1;
    }

    // 设置服务器地址结构体
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080); // 端口号8080
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 本地回环地址

    // 连接服务器
    // need to use command nc -l 8080, to startup a server program
    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "connect failed\n";
        close(sockfd);
        return 1;
    }

    // 发送消息到服务器
    const char* msg = "Hello, server!";
    send(sockfd, msg, strlen(msg), 0);

    // 接收服务器返回的数据
    char buffer[1024] = {0};
    int n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}