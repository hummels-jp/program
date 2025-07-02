#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <chrono>

std::shared_mutex rw_mutex;
int shared_data = 0;

void reader(int id) {
    for (int i = 0; i < 3; ++i) {
        std::shared_lock<std::shared_mutex> lock(rw_mutex);
        std::cout << "Reader " << id << " reads shared_data = " << shared_data << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writer(int id) {
    for (int i = 0; i < 2; ++i) {
        std::unique_lock<std::shared_mutex> lock(rw_mutex);
        ++shared_data;
        std::cout << "Writer " << id << " updates shared_data to " << shared_data << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    std::vector<std::thread> threads;

    // Start readers
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(reader, i);
    }

    // Start writers
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(writer, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}