#include <iostream>
#include <csignal>
#include <unistd.h>

int main() {
    sigset_t set, oldset;

    // 初始化信号集为空，并添加 SIGINT
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    // 阻塞 SIGINT 信号
    if (sigprocmask(SIG_BLOCK, &set, &oldset) == -1) {
        perror("sigprocmask");
        return 1;
    }

    std::cout << "SIGINT blocked. Press Ctrl+C, nothing will happen for 5 seconds..." << std::endl;
    sleep(5);

    // 解除阻塞
    if (sigprocmask(SIG_SETMASK, &oldset, nullptr) == -1) {
        perror("sigprocmask");
        return 1;
    }

    std::cout << "SIGINT unblocked. Press Ctrl+C to interrupt." << std::endl;
    sleep(5);