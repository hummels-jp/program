#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <sys/types.h>

int main() {
    const char* fifo_path = "/tmp/myfifo_cpp";
    mkfifo(fifo_path, 0666);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        // 子进程：读端
        int fd = open(fifo_path, O_RDONLY);
        char buf[100] = {0};
        read(fd, buf, sizeof(buf));
        std::cout << "子进程收到: " << buf << std::endl;
        close(fd);
    } else {
        // 父进程：写端
        int fd = open(fifo_path, O_WRONLY);
        const char* msg = "Hello from parent (FIFO)!";
        write(fd, msg, strlen(msg) + 1);
        close(fd);
    }
    // 可选：删除 FIFO 文件
    // unlink(fifo_path);
    return 0;
}
