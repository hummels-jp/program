#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex tmtx;

void work(int id) {
    using namespace std::chrono_literals;
    if (tmtx.try_lock_for(100ms)) {
        std::cout << "Thread " << id << " acquired the lock.\n";
        std::this_thread::sleep_for(200ms); // simulate work
        tmtx.unlock();
    } else {
        std::cout << "Thread " << id << " could not acquire the lock.\n";
    }
}

int main() {
    std::thread t1(work, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::thread t2(work, 2);

    t1.join();
    t2.join();
    return 0;
}