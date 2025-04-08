#include "head.h"
#include <iostream>

int main() {
    int a = 10, b = 5;

    std::cout << "Addition: " << add(a, b) << std::endl;
    std::cout << "Subtraction: " << subtract(a, b) << std::endl;
    std::cout << "Multiplication: " << multiply(a, b) << std::endl;
    std::cout << "Division: " << divide(a, b) << std::endl;

    return 0;
}