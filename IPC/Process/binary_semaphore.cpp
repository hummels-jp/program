#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

std::binary_semaphore empty(1); // 初始为1，表示缓冲区为空
std::binary_semaphore full(0);  // 初始为0，表示缓冲区无数据
int buffer = 0;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        empty.acquire(); // 等待缓冲区空
        buffer = i;
        std::cout << "生产者写入: " << buffer << std::endl;
        full.release();  // 通知有数据
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer() {
    for (int i = 1; i <= 5; ++i) {
        full.acquire(); // 等待有数据
        std::cout << "消费者读取: " << buffer << std::endl;
        empty.release(); // 通知缓冲区空
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
