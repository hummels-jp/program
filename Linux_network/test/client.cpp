#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    // 1. 创建socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // 2. 设置服务器地址
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 本地服务器

    // 3. 连接服务器
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        close(sockfd);
        exit(1);
    }

    // 4. 交互
    while (fgets(buf, BUF_SIZE, stdin) != NULL) {
        write(sockfd, buf, strlen(buf));
        ssize_t n = read(sockfd, buf, BUF_SIZE-1);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("From server: %s", buf);
    }

    close(sockfd);
    return 0;
}