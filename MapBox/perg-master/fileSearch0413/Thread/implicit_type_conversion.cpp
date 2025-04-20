#include <iostream>
#include <thread>
#include <string>

// Example 1: Implicit Conversion of Integer to Pointer
void threadTask1(int* ptr) {
    if (ptr) {
        std::cout << "Pointer value: " << *ptr << std::endl;
    } else {
        std::cout << "Null pointer received!" << std::endl;
    }
}

// Example 2: Implicit Conversion of String Literal to std::string
void threadTask2(const std::string& str) {
    std::cout << "String: " << str << std::endl;
}

// Example 3: Implicit Conversion of Temporary Object
class MyClass {
public:
    MyClass(int x) : value(x) {}
    void print() const {
        std::cout << "Value: " << value << std::endl;
    }

private:
    int value;
};

void threadTask3(MyClass obj) {
    obj.print();
}

// Example 4: Implicit Conversion of Function Pointer
void threadTask4(int x) {
    std::cout << "Value: " << x << std::endl;
}

int main() {
    // Example 1: Implicit Conversion of Integer to Pointer
    int value = 42;
    // Unsafe: `value` is implicitly converted to a pointer
    std::thread t1(threadTask1, value); // This will cause undefined behavior
    t1.join();

    // Example 2: Implicit Conversion of String Literal to std::string
    // Unsafe: string literal is not directly convertible to `std::string`
    std::thread t2(threadTask2, "Hello, World!");
    t2.join();

    // Example 3: Implicit Conversion of Temporary Object
    // Unsafe: temporary object may not be safely passed to the thread
    std::thread t3(threadTask3, 42);
    t3.join();

    // Example 4: Implicit Conversion of Function Pointer
    // Unsafe: incorrect function signature
    std::thread t4((void (*)(int))threadTask4, 42);
    t4.join();

    return 0;
}