#include <iostream>
#include <thread>
#include <chrono>

class Worker {
public:
    void doWork(int count) {
        for (int i = 1; i <= count; ++i) {
            std::cout << "Worker thread: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

int main() {
    Worker w;

    // 使用成员函数作为线程入口：必须传对象指针
    std::thread t(&Worker::doWork, &w, 5); // 等价于 w.doWork(5)

    std::cout << "Main thread is running..." << std::endl;

    t.join();
    std::cout << "Thread finished!" << std::endl;

    return 0;
}
