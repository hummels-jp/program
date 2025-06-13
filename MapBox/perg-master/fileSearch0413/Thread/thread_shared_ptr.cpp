#include <iostream>
#include <thread>
#include <memory>

void subThreadTask(std::shared_ptr<int> sharedValue) {
    std::cout << "Subthread started, shared value: " << *sharedValue << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    (*sharedValue) += 10;
    std::cout << "Subthread finished, updated value: " << *sharedValue << std::endl;
}

int main() {
    // Create a shared_ptr to manage the local variable
    std::shared_ptr<int> sharedValue = std::make_shared<int>(42);

    // Start a subthread and pass the shared_ptr
    std::thread subThread(subThreadTask, sharedValue);

    // Main thread continues to use the shared_ptr
    std::cout << "Main thread, initial value: " << *sharedValue << std::endl;

    // Wait for the subthread to finish
    subThread.join();

    // Access the updated value in the main thread
    std::cout << "Main thread, updated value: " << *sharedValue << std::endl;

    return 0;
}