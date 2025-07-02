#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile sig_atomic_t sig_flag = 0;

void handler(int sig) {
    sig_flag = 1;
}

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        // 子进程
        sleep(1); // 确保父进程已安装信号处理器
        printf("子进程发送 SIGUSR1 给父进程\n");
        kill(getppid(), SIGUSR1);
        exit(0);
    } else {
        // 父进程
        signal(SIGUSR1, handler);
        printf("父进程等待子进程信号...\n");
        while (!sig_flag) {
            pause(); // 等待信号
        }
        printf("父进程收到 SIGUSR1 信号\n");
        wait(NULL);
    }
    return 0;
}
