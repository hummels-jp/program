#include "calculator.h"
#include <stdexcept>


int divide(int a, int b)
{
    if (b == 0)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return a / b;
}