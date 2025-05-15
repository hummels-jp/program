#include <iostream>

// Difference between top-level const and low-level const
// Top-level const: qualifies the object itself (including the pointer itself), e.g. const int b, int* const p2;
// Low-level const: qualifies the content pointed to by the object, e.g. const int* p1, const int* const p3;

int main() {
    // Pointer to const: the content pointed to by the pointer is constant, cannot modify the value through the pointer
    const int value1 = 100; // top-level const
    const int* constPointer = &value1; // low-level const
    // *constPointer = 200; // Error: cannot modify the value pointed to by the pointer

    // Const pointer: the pointer itself is constant, cannot point to another address
    int value2 = 200;
    int* const constantPointer = &value2; // top-level const
    *constantPointer = 300; // OK: can modify the value pointed to by the pointer
    // constantPointer = &value1; // Error: cannot modify the pointer itself


    int a = 10;
    const int b = 20;        // top-level const, b itself is constant
    const int* p1 = &a;      // low-level const, *p1 cannot be modified through p1
    int* const p2 = &a;      // top-level const, p2 itself is constant, cannot point elsewhere
    const int* const p3 = &b;// both top-level and low-level const

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "*p1 = " << *p1 << std::endl;
    std::cout << "*p2 = " << *p2 << std::endl;
    std::cout << "*p3 = " << *p3 << std::endl;

    // b = 30;      // Error: b is top-level const
    // *p1 = 40;    // Error: *p1 is low-level const
    // p2 = &b;     // Error: p2 is top-level const
    // *p3 = 50;    // Error: *p3 is low-level const
    // p3 = &a;     // Error: p3 is top-level const

    const int x = 10; // top-level const
    const int*p1 = &x; // low-level const

    return 0;
}