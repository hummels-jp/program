#include <iostream>
#include <csignal>
#include <unistd.h>

void signalHandler(int signum) {
    std::cout << "接收到信号: " << signum << std::endl;
}

int main() {
    // 声明信号集
    sigset_t newset;
    
    // 初始化空信号集
    if (sigemptyset(&newset) == -1) {
        std::cerr << "sigemptyset失败" << std::endl;
        return 1;
    }
    
    // 向信号集添加SIGINT信号(Ctrl+C)
    if (sigaddset(&newset, SIGINT) == -1) {
        std::cerr << "sigaddset失败" << std::endl;
        return 1;
    }
    
    // 设置信号处理函数
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sa.sa_flags = 0;
    
    // 将信号集赋值给sa.sa_mask
    // 这表示在执行信号处理函数时阻塞这些信号
    sa.sa_mask = newset;
    
    // 注册信号处理函数
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        std::cerr << "sigaction失败" << std::endl;
        return 1;
    }
    
    std::cout << "程序运行中，按Ctrl+C触发SIGINT信号..." << std::endl;
    
    // 让程序继续运行
    while(1) {
        sleep(1);
    }
    
    return 0;
}