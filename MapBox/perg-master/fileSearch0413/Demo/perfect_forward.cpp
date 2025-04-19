#include <iostream>
#include <utility>
#include <string>

// A function to demonstrate different types of arguments
// This function overloads for lvalue reference, const lvalue reference, and rvalue reference
void process(int& x) {
    std::cout << "Lvalue reference: " << x << std::endl;
}

// This overload is for const lvalue reference
void process(const int& x) {
    std::cout << "Const lvalue reference: " << x << std::endl;
}

// This overload is for rvalue reference
void process(int&& x) {
    std::cout << "Rvalue reference: " << x << std::endl;
}

// A wrapper function that uses perfect forwarding
template <typename T>
void forwardToProcess(T&& arg) {
    process(std::forward<T>(arg));
}

int main() {
    int x = 10;
    const int cx = 20;

    std::cout << "Passing lvalue (x):" << std::endl;
    forwardToProcess(x);

    std::cout << "\nPassing const lvalue (cx):" << std::endl;
    forwardToProcess(cx);

    std::cout << "\nPassing rvalue (30):" << std::endl;
    forwardToProcess(30);

    return 0;
}