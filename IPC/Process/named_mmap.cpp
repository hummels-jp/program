#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

int main() {
    const char* shm_name = "/my_named_mmap";
    const int size = 4096;

    // 创建或打开命名共享内存对象
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open error");
        return 1;
    }
    ftruncate(shm_fd, size);

    void* addr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap error");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        // 子进程写入共享内存
        strcpy((char*)addr, "Hello from child (named mmap)!");
        munmap(addr, size);
        close(shm_fd);
    } else {
        // 父进程等待子进程写入
        wait(nullptr);
        std::cout << "父进程读取: " << (char*)addr << std::endl;
        munmap(addr, size);
        close(shm_fd);
        shm_unlink(shm_name); // 删除命名共享内存对象
    }
    return 0;
}