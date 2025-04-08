#include "calculator.h"
#include <iostream>
using namespace std;

int main()
{
    int a = 5;
    int b = 3;

    cout << "Addition: " << add(a, b) << endl;
    cout << "Subtraction: " << subtract(a, b) << endl;
    cout << "Multiplication: " << multiply(a, b) << endl;
    cout << "Division: " << divide(a, b) << endl;
    return 0;
}