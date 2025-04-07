#include "../include/head.h"
#include <stdexcept>

double divide(int a, int b)
{
    if (b == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return static_cast<double>(a) / b;
}