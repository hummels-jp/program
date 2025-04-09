#include <iostream>
#include <future>
#include <thread>
#include <chrono>

#include "async.h"

// A function to simulate a long-running task
int longRunningTask(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    return seconds;
}

int async_demo() {
    std::cout << "Starting async example..." << std::endl;

    // Launch an asynchronous task
    std::future<int> result = std::async(std::launch::async, longRunningTask, 5);

    // Do some other work while the async task runs
    std::cout << "Doing some work in main thread..." << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Main thread working: " << i + 1 << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Get the result of the async task
    int taskResult = result.get();
    std::cout << "Async task completed after " << taskResult << " seconds." << std::endl;

    return 0;
}