#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstring>

// 第一个信号处理函数
void simpleHandler(int signum) {
    std::cout << "简单处理函数: 接收到信号 " << signum << std::endl;
}

// 更高级的信号处理函数，使用sigaction提供的额外信息
void advancedHandler(int signum, siginfo_t *info, void *context) {
    std::cout << "高级处理函数: 接收到信号 " << signum << std::endl;
    
    // 输出关于信号的额外信息
    if (info != nullptr) {
        std::cout << "  信号发送者的进程ID: " << info->si_pid << std::endl;
        std::cout << "  用户ID: " << info->si_uid << std::endl;
        std::cout << "  信号码: " << info->si_code << std::endl;
        
        // 如果是SIGFPE（浮点异常）打印错误类型
        if (signum == SIGFPE) {
            std::cout << "  浮点异常类型: ";
            switch (info->si_code) {
                case FPE_INTDIV: std::cout << "整数除零"; break;
                case FPE_INTOVF: std::cout << "整数溢出"; break;
                case FPE_FLTDIV: std::cout << "浮点除零"; break;
                case FPE_FLTOVF: std::cout << "浮点上溢"; break;
                case FPE_FLTUND: std::cout << "浮点下溢"; break;
                case FPE_FLTRES: std::cout << "浮点不精确结果"; break;
                case FPE_FLTINV: std::cout << "浮点无效操作"; break;
                case FPE_FLTSUB: std::cout << "下标超出范围"; break;
                default: std::cout << "未知"; break;
            }
            std::cout << std::endl;
        }
        
        // 如果是SIGSEGV（段错误）打印错误地址
        if (signum == SIGSEGV) {
            std::cout << "  错误地址: " << info->si_addr << std::endl;
        }
    }
}

// 触发一个除零错误的函数
void triggerDivideByZero() {
    int a = 1;
    int b = 0;
    int c = a / b;  // 这将触发SIGFPE
    std::cout << "结果是 " << c << std::endl;  // 这行不会执行
}

// 触发一个段错误的函数
void triggerSegfault() {
    int *ptr = nullptr;
    *ptr = 42;  // 这将触发SIGSEGV
}

int main() {
    std::cout << "sigaction 示例程序\n" << std::endl;
    
    // 演示1: 使用基本的signal函数
    std::cout << "演示1: 使用标准signal()函数" << std::endl;
    if (signal(SIGINT, simpleHandler) == SIG_ERR) {
        std::cerr << "无法设置SIGINT的信号处理函数" << std::endl;
        return 1;
    }
    
    std::cout << "按Ctrl+C触发SIGINT..." << std::endl;
    sleep(3);  // 给用户时间触发信号
    
    // 演示2: 使用sigaction函数
    std::cout << "\n演示2: 使用sigaction()函数" << std::endl;
    
    // 设置SIGUSR1的处理函数
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    
    // 使用sa_handler字段（类似于signal()）
    sa.sa_handler = simpleHandler;
    
    // 设置要在信号处理期间阻塞的信号
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGQUIT);  // 在处理SIGUSR1时阻塞SIGQUIT
    
    // 设置标志
    sa.sa_flags = 0;
    
    if (sigaction(SIGUSR1, &sa, nullptr) == -1) {
        std::cerr << "无法设置SIGUSR1的信号处理函数: " << strerror(errno) << std::endl;
        return 1;
    }
    
    std::cout << "发送SIGUSR1信号到自己..." << std::endl;
    kill(getpid(), SIGUSR1);
    
    // 演示3: 使用带有SA_SIGINFO标志的sigaction
    std::cout << "\n演示3: 使用带有SA_SIGINFO标志的sigaction()" << std::endl;
    
    memset(&sa, 0, sizeof(sa));
    
    // 使用sa_sigaction字段（提供更多信息的处理函数）
    sa.sa_sigaction = advancedHandler;
    sigemptyset(&sa.sa_mask);
    
    // SA_SIGINFO表示使用sa_sigaction字段而不是sa_handler
    sa.sa_flags = SA_SIGINFO;
    
    if (sigaction(SIGSEGV, &sa, nullptr) == -1) {
        std::cerr << "无法设置SIGSEGV的信号处理函数: " << strerror(errno) << std::endl;
        return 1;
    }
    
    if (sigaction(SIGFPE, &sa, nullptr) == -1) {
        std::cerr << "无法设置SIGFPE的信号处理函数: " << strerror(errno) << std::endl;
        return 1;
    }
    
    std::cout << "演示3a: 触发除零错误(SIGFPE)..." << std::endl;
    try {
        triggerDivideByZero();
    } catch (...) {
        std::cout << "捕获到C++异常" << std::endl;
    }
    
    std::cout << "\n演示3b: 触发段错误(SIGSEGV)..." << std::endl;
    try {
        triggerSegfault();
    } catch (...) {
        std::cout << "捕获到C++异常" << std::endl;
    }
    
    std::cout << "\n程序继续执行，按Ctrl+C退出" << std::endl;
    sleep(5);
    
    return 0;
}