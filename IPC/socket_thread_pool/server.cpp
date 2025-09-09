#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ThreadPool.h"
#include <thread>

#define PORT 8080
#define BUF_SIZE 1024

// Function to handle a single client connection
void handle_client(int connfd) {
    char buf[BUF_SIZE];
    while (1) {
        ssize_t n = read(connfd, buf, BUF_SIZE-1);
        if (n <= 0) break;
        buf[n] = '\0';
        for (int i = 0; i < n; ++i) buf[i] = toupper((unsigned char)buf[i]);
        write(connfd, buf, n);
    }
    printf("Client disconnected.\n");
    close(connfd);
}

int main() 
{
    int listenfd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_len;

    // 1. Create listen socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        exit(1);
    }

    // 2. Bind address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        close(listenfd);
        exit(1);
    }

    // 3. Listen
    if (listen(listenfd, 10) < 0) {
        perror("listen");
        close(listenfd);
        exit(1);
    }
    printf("Server listening on port %d...\n", PORT);

    // 4. Create thread pool
    ThreadPool pool(4, 8); // min 4, max 8 threads

    // 5. Accept clients in a loop and hand off to thread pool
    while (1) {
        client_len = sizeof(client_addr);
        int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_len);
        if (connfd < 0) {
            perror("accept");
            continue;
        }
        printf("Client connected.\n");
        pool.enqueue(handle_client, connfd);
    }

    close(listenfd);
    return 0;
}