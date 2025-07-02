#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define SHM_NAME "/my_shm"
#define SHM_SIZE 4096

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "用法: " << argv[0] << " [w|r]" << endl;
        return 1;
    }

    int shm_fd;
    if (argv[1][0] == 'w') {
        // 写进程
        shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        if (shm_fd < 0) {
            perror("shm_open");
            return 1;
        }
        ftruncate(shm_fd, SHM_SIZE); // 设置共享内存大小

        void* ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            perror("mmap");
            return 1;
        }

        const char* msg = "Hello from writer process!";
        memcpy(ptr, msg, strlen(msg) + 1);

        munmap(ptr, SHM_SIZE);
        close(shm_fd);
        cout << "Writer finished." << endl;
    } else if (argv[1][0] == 'r') {
        // 读进程
        shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
        if (shm_fd < 0) {
            perror("shm_open");
            return 1;
        }

        void* ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            perror("mmap");
            return 1;
        }

        cout << "Reader received: " << (char*)ptr << endl;

        munmap(ptr, SHM_SIZE);
        close(shm_fd);
        // 可选：shm_unlink(SHM_NAME); // 读完后删除共享内存对象
    } else {
        cout << "参数错误，只能用 w 或 r" << endl;
    }

    return 0;
}