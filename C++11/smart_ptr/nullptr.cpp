#include <iostream>

// This program demonstrates the use of nullptr in C++11.
void func(int* ptr) {
    if (ptr) {
        std::cout << "Pointer is not null, value: " << *ptr << std::endl;
    } else {
        std::cout << "Pointer is null" << std::endl;
    }
}

void compareNullptrAndNULL() {
    int* ptr1 = nullptr; // C++11 nullptr
    int* ptr2 = NULL;    // Traditional NULL

    if (ptr1 == nullptr) {
        std::cout << "ptr1 is nullptr" << std::endl;
    }

    if (ptr2 == NULL) {
        std::cout << "ptr2 is NULL" << std::endl;
    }

    // Comparing nullptr and NULL
    if (ptr1 == ptr2) {
        std::cout << "nullptr and NULL are equivalent when compared" << std::endl;
    }
}

void func(void* ptr) {
    if (ptr) {
        std::cout << "Void pointer is not null" << std::endl;
    } else {
        std::cout << "Void pointer is null" << std::endl;
    }
}

void func(int value) {
    std::cout << "Integer value: " << value << std::endl;
}

int main() {
    int* p1 = nullptr; // Using nullptr to initialize a null pointer
    func(p1);

    int value = 42;
    int* p2 = &value; // Pointer to a valid integer
    func(p2);

    compareNullptrAndNULL();

    func(static_cast<void*>(nullptr)); // Explicitly cast nullptr to void*

    func(static_cast<int>(NULL)); // Explicitly cast NULL to int

    return 0;
}