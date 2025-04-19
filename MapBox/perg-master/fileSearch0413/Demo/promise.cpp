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
        // 1. Using std::promise with a free function
        std::promise<int> promise1;
        std::future<int> future1 = promise1.get_future();
        std::thread thread1([](std::promise<int>&& promise, int x, int y) {
            try {
                promise.set_value(freeFunction(x, y));
            } catch (...) {
                promise.set_exception(std::current_exception());
            }
        }, std::move(promise1), 10, 20);
        thread1.join();
        std::cout << "Result from freeFunction: " << future1.get() << std::endl;

        // 2. Using std::promise with a lambda expression
        std::promise<int> promise2;
        std::future<int> future2 = promise2.get_future();
        std::thread thread2([](std::promise<int>&& promise, int x, int y) {
            try {
                promise.set_value(x / y);
            } catch (...) {
                promise.set_exception(std::current_exception());
            }
        }, std::move(promise2), 20, 5);
        thread2.join();
        std::cout << "Result from lambda: " << future2.get() << std::endl;

        // 3. Using std::promise with a member function
        MyClass obj;
        std::promise<int> promise3;
        std::future<int> future3 = promise3.get_future();
        std::thread thread3([](std::promise<int>&& promise, const MyClass* obj, int x, int y) {
            try {
                promise.set_value(obj->memberFunction(x, y));
            } catch (...) {
                promise.set_exception(std::current_exception());
            }
        }, std::move(promise3), &obj, 5, 6);
        thread3.join();
        std::cout << "Result from memberFunction: " << future3.get() << std::endl;

        // 4. Using std::promise with a function object (functor)
        Functor functor;
        std::promise<int> promise4;
        std::future<int> future4 = promise4.get_future();
        std::thread thread4([](std::promise<int>&& promise, Functor functor, int x, int y) {
            try {
                promise.set_value(functor(x, y));
            } catch (...) {
                promise.set_exception(std::current_exception());
            }
        }, std::move(promise4), functor, 15, 5);
        thread4.join();
        std::cout << "Result from functor: " << future4.get() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}