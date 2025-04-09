#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
using namespace std;

#include "atomic.h"

// This program demonstrates the use of std::atomic to safely increment a counter from multiple threads.
std::atomic<int> counter(0);

// Function to increment the counter in a thread-safe manner
void incrementCounter(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // Use fetch_add to atomically increment the counter
        
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int atomic_demo() {
    const int numThreads = 4;
    const int iterations = 1000;

    std::vector<std::thread> threads;

    // Create multiple threads to increment the counter
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter, iterations);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final counter value: " << counter.load(std::memory_order_relaxed) << std::endl;

    return 0;
}