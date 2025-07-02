#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 子进程：从管道读取数据
        close(fd[1]); // 关闭写端
        char buffer[100];
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            cout << "Child received: " << buffer << endl;
        }
        close(fd[0]);
    } else {
        // 父进程：向管道写入数据
        close(fd[0]); // 关闭读端
        const char* msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
    }
    return 0;
}