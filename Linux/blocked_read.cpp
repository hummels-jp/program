#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main() {
    char buf[BUF_SIZE];
    ssize_t bytes_read;

    // 从标准输入阻塞读取，直到遇到 EOF（Ctrl+D）
    while ((bytes_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        ssize_t bytes_written = 0;
        while (bytes_written < bytes_read) {
            ssize_t result = write(STDOUT_FILENO, buf + bytes_written, bytes_read - bytes_written);
            if (result < 0) {
                perror("写入标准输出失败");
                return 1;
            }
            bytes_written += result;
        }
    }
    if (bytes_read < 0) {
        perror("读取标准输入失败");
        return 1;
    }
    return 0;
}