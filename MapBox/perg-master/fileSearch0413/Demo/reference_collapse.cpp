#include <iostream>
#include <type_traits>

// A helper function to print the type
template <typename T>
void printType() {
    if constexpr (std::is_lvalue_reference<T>::value) {
        std::cout << "lvalue reference";
    } else if constexpr (std::is_rvalue_reference<T>::value) {
        std::cout << "rvalue reference";
    } else {
        std::cout << "non-reference";
    }
    std::cout << std::endl;
}

// A template function to demonstrate reference collapsing
template <typename T>
void referenceCollapse(T&& arg) {
    std::cout << "T: ";
    printType<T>();
    std::cout << "T&&: ";
    printType<decltype(arg)>();
}

int main() {
    int x = 10;
    const int cx = 20;

    std::cout << "Passing lvalue (x):" << std::endl;
    referenceCollapse(x);

    std::cout << "\nPassing const lvalue (cx):" << std::endl;
    referenceCollapse(cx);

    std::cout << "\nPassing rvalue (10):" << std::endl;
    referenceCollapse(10);

    return 0;
}