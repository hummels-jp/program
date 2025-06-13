#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

#define BUF_SIZE 4096

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("用法: %s <源文件> <目标文件>\n", argv[0]);
        return 1;
    }
    // open the file in the read only mode
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("打开源文件失败");
        return 1;
    }

    // 0644 rw-r--r--
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("打开/创建目标文件失败");
        close(src_fd);
        return 1;
    }

    char buf[BUF_SIZE];
    ssize_t bytes_read, bytes_written;
    while ((bytes_read = read(src_fd, buf, BUF_SIZE)) > 0) {
        char* out_ptr = buf;
        ssize_t to_write = bytes_read;
        while (to_write > 0) {
            bytes_written = write(dest_fd, out_ptr, to_write);
            if (bytes_written <= 0) {
                perror("写入目标文件失败");
                close(src_fd);
                close(dest_fd);
                return 1;
            }
            to_write -= bytes_written;
            out_ptr += bytes_written;
        }
    }

    if (bytes_read < 0) {
        perror("读取源文件失败");
    }

    close(src_fd);
    close(dest_fd);

    printf("文件复制完成。\n");
    return 0;
}