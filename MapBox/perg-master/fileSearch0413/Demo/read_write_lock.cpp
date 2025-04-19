#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <vector>
#include <chrono>

std::shared_mutex rwLock; // A shared mutex for read-write locking
int sharedResource = 0;   // A shared resource

// Reader function
void reader(int id) {
    for (int i = 0; i < 3; ++i) {
        std::shared_lock<std::shared_mutex> lock(rwLock); // Acquire shared (read) lock
        std::cout << "Reader " << id << " reads sharedResource: " << sharedResource << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate read delay
    }
}

// Writer function
void writer(int id, int increment) {
    for (int i = 0; i < 3; ++i) {
        std::unique_lock<std::shared_mutex> lock(rwLock); // Acquire unique (write) lock
        sharedResource += increment;
        std::cout << "Writer " << id << " updates sharedResource to: " << sharedResource << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Simulate write delay
    }
}

int main() {
    std::vector<std::thread> threads;

    // Create reader threads
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(reader, i);
    }

    // Create writer threads
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(writer, i, 10);
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final value of sharedResource: " << sharedResource << std::endl;

    return 0;
}