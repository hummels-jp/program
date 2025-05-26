#include <iostream>
#include <utility>

class MyArray {
private:
    int* data;
    size_t size;

public:
    // Constructor
    MyArray(size_t size) : size(size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0; // Initialize with 0
        }
        std::cout << "Constructor called\n";
    }

    // Copy Constructor
    MyArray(const MyArray& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Copy Constructor called\n";
    }

    // Move Constructor
    MyArray(MyArray&& other) noexcept : data(nullptr), size(0) {
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move Constructor called\n";
    }
    // Copy Assignment Operator
    MyArray& operator=(const MyArray& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }

        delete[] data; // Free existing resources

        size = other.size;
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Copy Assignment Operator called\n";
        return *this;
    }

    // Move Assignment Operator
    MyArray& operator=(MyArray&& other) noexcept {
        if (this == &other) {
            return *this; // Handle self-assignment
        }

        delete[] data; // Free existing resources

        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;

        std::cout << "Move Assignment Operator called\n";
        return *this;
    }
    // Destructor
    ~MyArray() {
        delete[] data;
        std::cout << "Destructor called\n";
    }

    // Print function for testing
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    MyArray arr1(5); // Constructor
    arr1.print();

    MyArray arr2 = arr1; // Copy Constructor
    arr2.print();

    MyArray arr3 = std::move(arr1); // Move Constructor
    arr3.print();

    int&& a1 = 1; // rvalue reference
    auto a2 = a1; // lvalue reference

    return 0;
}