#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    } else if (pid == 0) {
        // 子进程：执行 ls 命令
        std::cout << "Child: executing ls..." << std::endl;
        execl("/bin/ls", "ls", "-l", "./", (char*)NULL);
        // 如果 execl 成功，下面的代码不会执行
        std::cerr << "execl failed!" << std::endl;
        return 1;
    } else {
        // 父进程：等待子进程结束
        int status;
        waitpid(pid, &status, 0);
        std::cout << "Parent: child finished." << std::endl;
    }
    return 0;
}