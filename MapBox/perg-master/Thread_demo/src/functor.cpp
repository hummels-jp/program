#include <iostream>
#include "functor.h"
#include <thread>
using namespace std;
// A simple functor
class MultiplyBy {
public:
    explicit MultiplyBy(int factor) : factor_(factor) {}

    // Overloading the operator() to make it callable like a function
    int operator()(int value) const {
        cout << "Functor called with value: " << value << std::endl;
        return value * factor_;
    }

private:
    int factor_;
};

int functor_demo() {
    MultiplyBy multiplyBy3(3);
    MultiplyBy multiplyBy5(5);

    int value = 5;
    // Using the functor to multiply the value
    // The functor is called like a function
    // use the object like function 
    std::cout << "Result: " << multiplyBy3(value) << std::endl;
    std::cout << "Result: " << multiplyBy5(value) << std::endl;

    thread t1((MultiplyBy(4)), 5);
    t1.join();

    return 0;
}