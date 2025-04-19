#include <iostream>
#include <future>
#include <thread>
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
    // 1. Using std::async with a free function
    auto future1 = std::async(std::launch::async, freeFunction, 10, 20);
    std::cout << "Result from freeFunction: " << future1.get() << std::endl;

    // 2. Using std::async with a lambda expression
    auto future2 = std::async(std::launch::async, [](int x, int y) {
        return x / y;
    }, 20, 5);
    std::cout << "Result from lambda: " << future2.get() << std::endl;

    // 3. Using std::async with a member function
    MyClass obj;
    auto future3 = std::async(std::launch::async, &MyClass::memberFunction, &obj, 5, 6);
    std::cout << "Result from memberFunction: " << future3.get() << std::endl;

    // 4. Using std::async with a function object (functor)
    Functor functor;
    auto future4 = std::async(std::launch::async, functor, 15, 5);
    std::cout << "Result from functor: " << future4.get() << std::endl;

    return 0;
}