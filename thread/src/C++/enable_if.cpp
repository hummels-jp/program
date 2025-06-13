#include <type_traits>
#include <iostream>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print(T value) {
    std::cout << "Integral type: " << value << std::endl;
}

template <typename T>
typename std::enable_if<!std::is_integral<T>::value, void>::type
print(T value) {
    std::cout << "Non-integral type: " << value << std::endl;
}

int main() {
    print(42);           // Outputs: Integral type: 42
    print(3.14);         // Outputs: Non-integral type: 3.14
    return 0;
}