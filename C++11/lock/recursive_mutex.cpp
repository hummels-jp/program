#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rec_mtx;
int counter = 0;

void recursive_increase(int depth) {
    if (depth <= 0) return;
    rec_mtx.lock();
    ++counter;
    std::cout << "Thread " << std::this_thread::get_id() 
              << " increased counter to " << counter 
              << " at depth " << depth << std::endl;
    recursive_increase(depth - 1);
    rec_mtx.unlock();
}

int main() {
    std::thread t1(recursive_increase, 3);
    std::thread t2(recursive_increase, 3);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl;
    return 0;
}