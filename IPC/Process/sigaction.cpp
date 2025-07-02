#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t sig_flag = 0;

void handler(int sig, siginfo_t* info, void* context) {
    printf("收到来自进程 %d 的信号 %d\n", info->si_pid, sig);
    sig_flag = 1;
}

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "send") == 0) {
        // 发送进程
        pid_t target_pid;
        printf("请输入目标进程PID: ");
        scanf("%d", &target_pid);
        printf("发送 SIGUSR1 给进程 %d\n", target_pid);
        kill(target_pid, SIGUSR1);
        return 0;
    }

    // 接收进程
    struct sigaction act;
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);

    printf("接收进程PID: %d，等待信号...\n", getpid());
    while (!sig_flag) {
        pause();
    }
    printf("信号处理完毕，退出\n");
    return 0;
}
