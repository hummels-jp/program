#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    } else if (pid == 0) {
        // 子进程
        std::cout << "Child process, PID=" << getpid() << std::endl;
        sleep(2); // 模拟子进程的工作
        std::cout << "Child process exits." << std::endl;
        return 42; // 子进程返回码
    } else {
        // 父进程
        int status;
        pid_t child_pid = wait(&status); // 等待子进程结束
        std::cout << "Parent process, waited for child PID=" << child_pid << std::endl;
        if (WIFEXITED(status)) {
            std::cout << "Child exited with code " << WEXITSTATUS(status) << std::endl;
        }
    }
    return 0;
}