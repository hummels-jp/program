#include <iostream>
#include <cstddef> // For offsetof

struct A {
    char c;   // 1 byte
    int i;    // 4 bytes
    double d; // 8 bytes
};

struct B {
    double d; // 8 bytes
    int i;    // 4 bytes
    char c;   // 1 byte
};

#pragma pack(push, 1) // Disable padding
struct C {
    char c;   // 1 byte
    int i;    // 4 bytes
    double d; // 8 bytes
};
#pragma pack(pop) // Restore default alignment

int main() {
    // Default alignment
    std::cout << "Struct A:" << std::endl;
    std::cout << "Size of A: " << sizeof(A) << std::endl;
    std::cout << "Offset of c: " << offsetof(A, c) << std::endl;
    std::cout << "Offset of i: " << offsetof(A, i) << std::endl;
    std::cout << "Offset of d: " << offsetof(A, d) << std::endl;

    std::cout << "\nStruct B:" << std::endl;
    std::cout << "Size of B: " << sizeof(B) << std::endl;
    std::cout << "Offset of d: " << offsetof(B, d) << std::endl;
    std::cout << "Offset of i: " << offsetof(B, i) << std::endl;
    std::cout << "Offset of c: " << offsetof(B, c) << std::endl;

    // Packed alignment
    std::cout << "\nStruct C (packed):" << std::endl;
    std::cout << "Size of C: " << sizeof(C) << std::endl;
    std::cout << "Offset of c: " << offsetof(C, c) << std::endl;
    std::cout << "Offset of i: " << offsetof(C, i) << std::endl;
    std::cout << "Offset of d: " << offsetof(C, d) << std::endl;

    return 0;
}