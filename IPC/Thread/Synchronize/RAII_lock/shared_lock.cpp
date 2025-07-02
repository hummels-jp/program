#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

std::shared_mutex rw_mutex;
int value = 0;

void reader(int id) {
    for (int i = 0; i < 6; ++i) {
        std::shared_lock<std::shared_mutex> lock(rw_mutex); // 共享锁，多个读线程可并发
        std::cout << "读线程 " << id << " 读取 value: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void writer(int id) {
    for (int i = 0; i < 6; ++i) {
        std::unique_lock<std::shared_mutex> lock(rw_mutex); // 独占锁，写线程独占
        ++value;
        std::cout << "写线程 " << id << " 修改 value: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main() {
    std::vector<std::thread> threads;
    threads.emplace_back(reader, 1);
    threads.emplace_back(reader, 2);
    // 让读线程先运行一段时间
    std::this_thread::sleep_for(std::chrono::milliseconds(150));

    threads.emplace_back(writer, 1);
    threads.emplace_back(writer, 2);

    for (auto& t : threads) t.join();
    return 0;
}