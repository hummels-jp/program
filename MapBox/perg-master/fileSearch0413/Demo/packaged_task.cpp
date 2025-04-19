#include <iostream>
#include <thread>
#include <future>
#include <functional>

// A free function
int freeFunction(int x, int y) {
    return x + y;
}

// A class with a member function
class MyClass {
public:
    int memberFunction(int x, int y) const {
        return x * y;
    }
};

// A function object (functor)
struct Functor {
    int operator()(int x, int y) const {
        return x - y;
    }
};

int main() {
    try {
        // 1. Using std::packaged_task with a free function
        std::packaged_task<int(int, int)> task1(freeFunction);
        std::future<int> future1 = task1.get_future();
        std::thread thread1(std::move(task1), 10, 20);
        thread1.join();
        std::cout << "Result from freeFunction: " << future1.get() << std::endl;

        // 2. Using std::packaged_task with a lambda expression
        std::packaged_task<int(int, int)> task2([](int x, int y) { return x / y; });
        std::future<int> future2 = task2.get_future();
        std::thread thread2(std::move(task2), 20, 5);
        thread2.join();
        std::cout << "Result from lambda: " << future2.get() << std::endl;

        // 3. Using std::packaged_task with a member function
        MyClass obj;
        std::packaged_task<int(const MyClass*, int, int)> task3(&MyClass::memberFunction);
        std::future<int> future3 = task3.get_future();
        std::thread thread3(std::move(task3), &obj, 5, 6);
        thread3.join();
        std::cout << "Result from memberFunction: " << future3.get() << std::endl;

        // 4. Using std::packaged_task with a function object (functor)
        Functor functor;
        std::packaged_task<int(int, int)> task4(functor);
        std::future<int> future4 = task4.get_future();
        std::thread thread4(std::move(task4), 15, 5);
        thread4.join();
        std::cout << "Result from functor: " << future4.get() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}