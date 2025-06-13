#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 4096

int main() {
    // 获取当前标准输入的文件状态标志
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (flags == -1) {
        perror("获取文件状态标志失败");
        return 1;
    }

    // 设置 O_NONBLOCK
    if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("设置非阻塞失败");
        return 1;
    }

    char buf[BUF_SIZE];
    ssize_t bytes_read;

    printf("请输入内容(非阻塞模式，输入 Ctrl+D 结束)：\n");

    while (1) {
        bytes_read = read(STDIN_FILENO, buf, BUF_SIZE);
        if (bytes_read > 0) {
            // 有数据可读，写到标准输出
            write(STDOUT_FILENO, buf, bytes_read);
        } else if (bytes_read == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // 当前没有数据可读，休眠一会儿，避免 CPU 占用过高
                // usleep(100000);  // 100 毫秒
                sleep(1); // 休眠1秒
                // 继续循环，等待数据
                printf("当前没有数据可读，等待中...\n");
                fflush(stdout); // 确保输出被刷新
                continue;
            } else {
                perror("读取标准输入出错");
                break;
            }
        } else { // bytes_read == 0，表示 EOF
            break;
        }
    }

    printf("\n读取结束。\n");
    return 0;
}