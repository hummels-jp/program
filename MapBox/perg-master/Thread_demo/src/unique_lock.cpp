#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
using namespace std::chrono_literals;

std::mutex mtx;

void print_message(const std::string& message, int id) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Thread " << id << ": " << message << std::endl;
    this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate some work
    lock.unlock(); // Explicitly unlock the mutex (optional, as it will be unlocked automatically)
    // The lock will be automatically released when the unique_lock goes out of scope
}

void thread_function(int id) {
    print_message("Hello from thread", id);
}

int main() {
    std::thread t1(thread_function, 1);
    std::thread t2(thread_function, 2);

    t1.join();
    t2.join();

    return 0;
}