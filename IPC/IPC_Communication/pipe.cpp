#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstring>

int main() {
    int fd[2];
    pid_t pid;
    char buf[100];

    // 创建管道
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 子进程：关闭写端，读取数据
        close(fd[1]);
        ssize_t n = read(fd[0], buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("子进程收到: %s\n", buf);
        }
        close(fd[0]);
    } else {
        // 父进程：关闭读端，写入数据
        close(fd[0]);
        const char* msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
        wait(NULL); // 等待子进程结束
    }
    return 0;
}