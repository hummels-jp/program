#include <iostream>
#include <csignal>

int main() {
    sigset_t set;
    // 初始化信号集为空
    if (sigemptyset(&set) == -1) {
        perror("sigemptyset");
        return 1;
    }

    // 添加 SIGINT 到信号集
    if (sigaddset(&set, SIGINT) == -1) {
        perror("sigaddset");
        return 1;
    }

    // 检查 SIGINT 是否在信号集中
    if (sigismember(&set, SIGINT)) {
        std::cout << "SIGINT is in the set." << std::endl;
    } else {
        std::cout << "SIGINT is NOT in the set." << std::endl;
    }
}