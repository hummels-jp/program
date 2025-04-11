#include <iostream>
#include <thread>
#include <mutex>
#include "mutex_demo.h"
using namespace std;

static std::mutex mtx;
int num =1;

void printOne() {
    while (true)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (num == 1)
        {
            /* code */
            std::cout << "1" << std::endl;
            num++;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    

     
}

void printTwo() {
    while (true)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (num == 2)
        {
            /* code */
            std::cout << "2" << std::endl;
            num--;
        }
    }
    
}

int mutex_demo() {
    std::thread t1(printOne);
    std::thread t2(printTwo);

    t1.join();
    t2.join();

    return 0;
}