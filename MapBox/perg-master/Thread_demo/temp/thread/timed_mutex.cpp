#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex mtx;

void try_to_lock(int id) {
    // Try to lock the mutex for up to 100 milliseconds
    if (mtx.try_lock_for(std::chrono::milliseconds(100))) {
        std::cout << "Thread " << id << " acquired the lock." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // simulate work
        mtx.unlock();
    } else {
        std::cout << "Thread " << id << " could NOT acquire the lock." << std::endl;
    }
}

int main() {
    std::thread t1(try_to_lock, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // slight delay to create contention
    std::thread t2(try_to_lock, 2);

    t1.join();
    t2.join();

    return 0;
}
