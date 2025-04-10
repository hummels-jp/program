#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include "packaged_task.h"

// A simple function to simulate some work
int workFunction(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * x;
}

int packaged_task_demo() {
    // Create a packaged_task wrapping the workFunction
    std::packaged_task<int(int)> task(workFunction);

    // Get the future associated with the packaged_task
    std::future<int> result = task.get_future();

    // Run the task in a separate thread
    std::thread t(std::move(task), 5);

    // Do some other work while the task is running
    std::cout << "Task is running in a separate thread...\n";

    // Wait for the result
    int value = result.get();
    std::cout << "Result from packaged_task: " << value << "\n";

    // Join the thread
    t.join();

    return 0;
}