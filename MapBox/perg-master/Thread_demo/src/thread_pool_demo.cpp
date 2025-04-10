#include "thread_pool_demo.h"
#include <iostream>

void thread_pool_demo() {
    ThreadPool pool(4); // Create a thread pool with 4 threads

    // Create an array of 20 tasks
    for (int i = 0; i < 20; ++i) {
        pool.enqueue([i]() {
            std::cout << "Processing task " << i 
                      << " on thread " << std::this_thread::get_id() 
                      << std::endl;
        });
    }
}