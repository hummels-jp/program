#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define FIFO_PATH "/tmp/myfifo"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "用法: " << argv[0] << " [w|r]" << endl;
        return 1;
    }

    // 创建FIFO（如果不存在）
    mkfifo(FIFO_PATH, 0666);

    if (argv[1][0] == 'w') {
        // 写进程
        int fd = open(FIFO_PATH, O_WRONLY);
        if (fd < 0) {
            perror("open");
            return 1;
        }
        const char* msg = "Hello from writer process!";
        write(fd, msg, strlen(msg));
        close(fd);
        cout << "Writer finished." << endl;
    } else if (argv[1][0] == 'r') {
        // 读进程
        int fd = open(FIFO_PATH, O_RDONLY);
        if (fd < 0) {
            perror("open");
            return 1;
        }
        char buf[100] = {0};
        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            cout << "Reader received: " << buf << endl;
        }
        close(fd);
    } else {
        cout << "参数错误，只能用 w 或 r" << endl;
    }

    return 0;
}