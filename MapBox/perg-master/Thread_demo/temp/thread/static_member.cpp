#include <iostream>
#include <thread>

class MyClass {
public:
    static void staticFunction(int id) {
        std::cout << "Thread started with id: " << id << std::endl;
    }
};

int main() {
    std::thread t(MyClass::staticFunction, 42);
    t.join();
    return 0;
}
