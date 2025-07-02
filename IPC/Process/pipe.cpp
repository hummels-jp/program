#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2];
    char buf[100];
    pipe(fd);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        // 子进程：从管道读取
        close(fd[1]); // 关闭写端
        read(fd[0], buf, sizeof(buf));
        printf("子进程收到: %s\n", buf);
        close(fd[0]);
    } else {
        // 父进程：向管道写入
        close(fd[0]); // 关闭读端
        const char* msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }
    return 0;
}
