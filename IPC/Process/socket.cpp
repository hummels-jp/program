#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/ipc_socket_demo"

int main() {
    int listen_fd, conn_fd, client_fd;
    struct sockaddr_un addr;
    char buf[100];

    listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listen_fd < 0) { perror("socket"); exit(1); }
    unlink(SOCKET_PATH);
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);
    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, 1);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 子进程：客户端
        sleep(1); // 确保服务器已监听
        client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        struct sockaddr_un cli_addr;
        memset(&cli_addr, 0, sizeof(cli_addr));
        cli_addr.sun_family = AF_UNIX;
        strcpy(cli_addr.sun_path, SOCKET_PATH);
        connect(client_fd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
        const char* msg = "Hello from client!";
        write(client_fd, msg, strlen(msg) + 1);
        close(client_fd);
        exit(0);
    } else {
        // 父进程：服务器
        conn_fd = accept(listen_fd, NULL, NULL);
        read(conn_fd, buf, sizeof(buf));
        printf("服务器收到: %s\n", buf);
        close(conn_fd);
        close(listen_fd);
        unlink(SOCKET_PATH);
    }
    return 0;
}
