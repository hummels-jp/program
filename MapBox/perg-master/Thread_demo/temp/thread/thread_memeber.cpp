#include <iostream>
#include <thread>
#include <chrono>

// A regular function used as thread entry point
void printNumbers(int count) {
    for (int i = 1; i <= count; ++i) {
        std::cout << "Thread: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work
    }
}

int main() {
    // Create thread and pass the function and its argument
    std::thread t(printNumbers, 5); // run printNumbers(5) in a new thread

    // Main thread continues
    std::cout << "Main thread continues working..." << std::endl;

    // Wait for the thread to finish
    t.join();

    std::cout << "Thread finished!" << std::endl;
    return 0;
}
