#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx; // A global mutex
int sharedResource = 0; // A shared resource

void incrementResource(int id, int increment) {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    std::cout << "Thread " << id << " is incrementing the resource by " << increment << std::endl;
    sharedResource += increment;
    std::cout << "Thread " << id << " updated the resource to " << sharedResource << std::endl;
    // The lock will be automatically released when the unique_lock goes out of scope
}

int main() {
    std::vector<std::thread> threads;

    // Create multiple threads
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(incrementResource, i, 10);
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final value of sharedResource: " << sharedResource << std::endl;

    return 0;
}