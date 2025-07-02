#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>

constexpr int buffer_size = 3; // 缓冲区大小
int buffer[buffer_size];
int in = 0, out = 0;

std::counting_semaphore<buffer_size> empty(buffer_size); // 初始有3个空位
std::counting_semaphore<buffer_size> full(0);            // 初始无数据
std::mutex mtx;

void producer() {
    for (int i = 1; i <= 10; ++i) {
        empty.acquire(); // 等待空位
        {
            std::lock_guard<std::mutex> lock(mtx);
            buffer[in] = i;
            std::cout << "生产者写入: " << buffer[in] << " 到槽 " << in << std::endl;
            in = (in + 1) % buffer_size;
        }
        full.release(); // 通知有数据
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumer() {
    for (int i = 1; i <= 10; ++i) {
        full.acquire(); // 等待有数据
        int val;
        {
            std::lock_guard<std::mutex> lock(mtx);
            val = buffer[out];
            std::cout << "消费者读取: " << val << " 从槽 " << out << std::endl;
            out = (out + 1) % buffer_size;
        }
        empty.release(); // 通知空位
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
