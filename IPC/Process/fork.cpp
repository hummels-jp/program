#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // 创建失败
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        // 子进程
        printf("子进程: pid=%d, 父进程pid=%d\n", getpid(), getppid());
    } else {
        // 父进程
        printf("父进程: pid=%d, 子进程pid=%d\n", getpid(), pid);
    }

    return 0;
}