#include <iostream>
#include <thread>

class Thread_Guard {
public:
    explicit Thread_Guard(std::thread& t) : thread(t) {}

    ~Thread_Guard() {
        if (thread.joinable()) {
            thread.join(); // Ensure the thread is joined before destruction
            std::cout << "Thread joined in Thread_Guard destructor." << std::endl;
        }
    }

    // Delete copy constructor and copy assignment to prevent copying
    Thread_Guard(const Thread_Guard&) = delete;
    Thread_Guard& operator=(const Thread_Guard&) = delete;

private:
    std::thread& thread; // Reference to the managed thread
};

void threadTask() {
    std::cout << "Thread is running..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    std::cout << "Thread finished work." << std::endl;
}

int main() {
    std::thread t(threadTask);

    // Use Thread_Guard to manage the thread
    Thread_Guard guard(t);

    std::cout << "Main thread continues..." << std::endl;

    // Thread_Guard ensures the thread is joined before exiting main
    return 0;
}