#include <iostream>
#include <functional>

// A free function
int freeFunction(int x, int y) {
    return x + y;
}

// A class with member and static member functions
class MyClass {
public:
    int memberFunction(int x, int y) const {
        return x * y;
    }

    static int staticMemberFunction(int x, int y) {
        return x - y;
    }
};

// A function object (functor)
struct Functor {
    int operator()(int x, int y) const {
        return x / y;
    }
};

int main() {
    // 1. Binding a free function
    auto boundFreeFunction = std::bind(freeFunction, 10, 20);
    std::cout << "Result of boundFreeFunction: " << boundFreeFunction() << std::endl;

    // 2. Binding a member function
    MyClass obj;
    auto boundMemberFunction = std::bind(&MyClass::memberFunction, &obj, 5, 6);
    std::cout << "Result of boundMemberFunction: " << boundMemberFunction() << std::endl;

    // 3. Binding a static member function
    auto boundStaticMemberFunction = std::bind(&MyClass::staticMemberFunction, 15, 5);
    std::cout << "Result of boundStaticMemberFunction: " << boundStaticMemberFunction() << std::endl;

    // 4. Binding a function object (functor)
    Functor functor;
    auto boundFunctor = std::bind(functor, 20, 4);
    std::cout << "Result of boundFunctor: " << boundFunctor() << std::endl;

    // 5. Binding with placeholders
    auto boundWithPlaceholders = std::bind(freeFunction, std::placeholders::_1, std::placeholders::_2);
    std::cout << "Result of boundWithPlaceholders(30, 40): " << boundWithPlaceholders(30, 40) << std::endl;

    return 0;
}