#include <iostream>
#include <thread>
#include <exception>
#include <stdexcept>

void subThreadTask() {
    try {
        std::cout << "Sub-thread is running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
        std::cout << "Sub-thread finished work." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception in sub-thread: " << e.what() << std::endl;
    }
}

int main() {
    std::thread subThread(subThreadTask);

    try {
        std::cout << "Main thread is throwing an exception..." << std::endl;
        throw std::runtime_error("Exception in main thread");
    } catch (const std::exception& e) {
        std::cerr << "Caught exception in main thread: " << e.what() << std::endl;

        // Ensure the sub-thread finishes before rethrowing the exception
        if (subThread.joinable()) {
            subThread.join();
        }

        // Rethrow the exception after the sub-thread has finished
        throw;
    }

    // Ensure the sub-thread is joined if no exception occurs
    if (subThread.joinable()) {
        subThread.join();
    }

    return 0;
}