#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

int main() {
    // 创建匿名共享内存
    int size = 4096;
    void* addr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
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
        strcpy((char*)addr, "Hello from child (mmap)!");
        munmap(addr, size);
    } else {
        // 父进程等待子进程写入
        wait(nullptr);
        std::cout << "父进程读取: " << (char*)addr << std::endl;
        munmap(addr, size);
    }
    return 0;
}