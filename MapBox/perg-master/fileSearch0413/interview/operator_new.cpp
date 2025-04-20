#include <iostream>
#include <new> // For placement new

class MyClass {
private:
    int value;

public:
    MyClass(int val) : value(val) {
        std::cout << "Constructor called for value: " << value << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called for value: " << value << std::endl;
    }

    void display() const {
        std::cout << "Value: " << value << std::endl;
    }

    // Overload operator new
    void* operator new(size_t size) {
        std::cout << "Custom operator new called, size: " << size << std::endl;
        void* ptr = ::operator new(size); // Use global operator new
        return ptr;
    }

    // Overload operator delete
    void operator delete(void* ptr) {
        std::cout << "Custom operator delete called" << std::endl;
        ::operator delete(ptr); // Use global operator delete
    }

    // Overload placement new
    void* operator new(size_t size, void* ptr) noexcept {
        std::cout << "Placement new called" << std::endl;
        return ptr;
    }
};

int main() {
    // Allocate memory and construct an object using custom operator new
    std::cout << "Creating a single object:" << std::endl;
    MyClass* obj = new MyClass(42); // Calls custom operator new and constructor
    obj->display();

    // Destroy the object and free memory using custom operator delete
    delete obj; // Calls destructor and custom operator delete

    // Allocate raw memory and manually call constructor and destructor
    std::cout << "\nManually managing memory:" << std::endl;
    void* rawMemory = ::operator new(sizeof(MyClass));        // Allocate raw memory using global operator new
    MyClass* manualObj = new (rawMemory) MyClass(99);         // Placement new to call constructor
    manualObj->display();
    manualObj->~MyClass();                                    // Manually call destructor
    ::operator delete(rawMemory);                             // Free raw memory using global operator delete

    return 0;
}