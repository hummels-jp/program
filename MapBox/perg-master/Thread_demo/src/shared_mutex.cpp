
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <chrono>
#include <mutex>
using namespace std;

#include "shared_mutex.h"

// 定义一个读写锁
static std::shared_mutex sharedMutex;
int sharedResource = 0;

// 读线程函数
void reader(int id) {
    for (int i = 0; i < 5; ++i) {
        std::shared_lock<std::shared_mutex> lock(sharedMutex);
        std::cout << "Reader " << id << " reads value: " << sharedResource << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// 写线程函数
void writer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::shared_mutex> lock(sharedMutex);
        ++sharedResource;
        std::cout << "Writer " << id << " updates value to: " << sharedResource << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int shared_mutext_demo() {
    // Create a vector to hold threads
    std::vector<std::thread> threads;

    // Create 8 reader threads
    for (int i = 0; i < 8; ++i) {
        // Create a reader thread and pass the thread ID
        threads.emplace_back(reader, i + 1);
    }

    // Create 2 writer threads
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(writer, i + 1);
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}