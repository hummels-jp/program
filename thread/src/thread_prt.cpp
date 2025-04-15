#include <iostream>
#include <memory>
#include <thread>

void threadFunction() {
    std::cout << "Thread is running!" << std::endl;
}

// 自定义删除器，用于在 std::unique_ptr 中使用
struct ThreadDeleter {
    void operator()(std::thread* t) const {
        if (t->joinable()) {
            t->join(); // 确保线程在销毁前被正确地join
        }
        delete t;
    }
};

int main() {
    // 使用 std::unique_ptr 并指定自定义删除器
    std::unique_ptr<std::thread, ThreadDeleter> threadPtr(new std::thread(threadFunction));

    std::cout << "Main thread is doing some work." << std::endl;

    // 离开作用域时，ThreadDeleter 会自动调用 join 并释放内存
    return 0;
}