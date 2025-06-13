#include <iostream>
#include <thread>

// Common function
void commonFunction() {
    std::cout << "Thread started using a common function." << std::endl;
}

// Functor (Callable Object)
class Functor {
public:
    void operator()() const {
        std::cout << "Thread started using a functor (callable object)." << std::endl;
    }
};

// Class with member and static member functions
class MyClass {
public:
    // Member function
    void memberFunction() const {
        std::cout << "Thread started using a class member function." << std::endl;
    }

    // Static member function
    static void staticMemberFunction() {
        std::cout << "Thread started using a class static member function." << std::endl;
    }
};

int main() {
    // 1. Using a common function
    std::thread thread1(commonFunction);

    // 2. Using a functor (callable object)
    Functor functor;
    std::thread thread2(functor);

    // 3. Using a lambda function
    std::thread thread3([]() {
        std::cout << "Thread started using a lambda function." << std::endl;
    });

    // 4. Using a class member function
    MyClass myObject;
    std::thread thread4(&MyClass::memberFunction, &myObject);

    // 5. Using a class static member function
    std::thread thread5(&MyClass::staticMemberFunction);

    // Join all threads
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();

    return 0;
}