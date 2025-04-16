#include <iostream>
#include <type_traits>

template <typename T>
concept Integral = std::is_integral_v<T>;


template <typename T>
requires Integral<T>
void print(T value) {
    std::cout << "Integral value: " << value << std::endl;
}

int main() {
    print(42);       // 合法，42 是整型
    // print(3.14);  // 非法，3.14 不是整型
}

