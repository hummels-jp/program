#include <iostream>

int main() {
    int a = 10;
    const int b = 20; // top-level const

    int c = b;        // OK: top-level const is ignored during copy
    std::cout << "c = " << c << std::endl;

    const int* p1 = &a; // low-level const
    int* p2 = nullptr;

    // p2 = p1; // Error: low-level const must match (cannot convert const int* to int*)
    p1 = p2;    // OK: can convert int* to const int*


    const int& ref1 = a; // OK: reference to const can bind to a non-const object
    // int& ref2 = b;    // Error: cannot bind non-const reference to a const object
    std::cout << "ref1 = " << ref1 << std::endl;
    return 0;
}