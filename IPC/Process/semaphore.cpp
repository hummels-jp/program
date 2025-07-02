#include <iostream>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

struct SharedData {
    char buffer[128];
    sem_t empty;
    sem_t full;
};

int main() {
    // 创建共享内存
    SharedData* data = (SharedData*)mmap(nullptr, sizeof(SharedData), PROT_READ | PROT_WRITE,
                                         MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(&data->empty, 1, 1); // 缓冲区初始为空
    sem_init(&data->full, 1, 0);  // 缓冲区初始为无数据

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        // 子进程：消费者
        for (int i = 0; i < 5; ++i) {
            sem_wait(&data->full); // 等待有数据
            std::cout << "消费者读取: " << data->buffer << std::endl;
            sem_post(&data->empty); // 释放空位
        }
        munmap(data, sizeof(SharedData));
    } else {
        // 父进程：生产者
        for (int i = 0; i < 5; ++i) {
            sem_wait(&data->empty); // 等待空位
            snprintf(data->buffer, sizeof(data->buffer), "消息 %d", i + 1);
            std::cout << "生产者写入: " << data->buffer << std::endl;
            sem_post(&data->full); // 通知有数据
            sleep(1);
        }
        wait(nullptr);
        munmap(data, sizeof(SharedData));
    }
    return 0;
}
