#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() 
{
    int listenfd, connfd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_len;
    char buf[BUF_SIZE];

    // 1. 创建listen socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        exit(1);
    }

    // 2. 绑定地址
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        close(listenfd);
        exit(1);
    }

    // 3. 监听
    if (listen(listenfd, 5) < 0) {
        perror("listen");
        close(listenfd);
        exit(1);
    }
    printf("Server listening on port %d...\n", PORT);

    // 4. 接受客户端连接 connect socket
    client_len = sizeof(client_addr);
    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_len);
    if (connfd < 0) {
        perror("accept");
        close(listenfd);
        exit(1);
    }
    printf("Client connected.\n");

    // 5. 循环接收、处理、发送
    while (1) {
        ssize_t n = read(connfd, buf, BUF_SIZE-1);
        if (n <= 0) break; // 客户端关闭或出错
        buf[n] = '\0';
        // 转换为大写
        for (int i = 0; i < n; ++i) buf[i] = toupper((unsigned char)buf[i]);
        write(connfd, buf, n);
    }
    printf("Client disconnected.\n");
    close(connfd);
    close(listenfd);
    return 0;
}