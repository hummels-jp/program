#include <iostream>
#include <vector>
using namespace std;

template <typename T>
bool compare(const T& a, const T& b) {
    cout << "Comparing values of type: " << typeid(T).name() << std::endl;
    return a < b;
}



int main() {
    int a = 5, b = 10;
    if (compare(a, b)) {
        std::cout << a << " is less than " << b << std::endl;
    } else {
        std::cout << a << " is not less than " << b << std::endl;
    }

    double x = 3.14, y = 2.71;
    if (compare(x, y)) {
        std::cout << x << " is less than " << y << std::endl;
    } else {
        std::cout << x << " is not less than " << y << std::endl;
    }

    string str1 = "apple", str2 = "banana";
    if (compare(str1, str2)) {
        std::cout << str1 << " is less than " << str2 << std::endl;
    } else {
        std::cout << str1 << " is not less than " << str2 << std::endl;
    }

    return 0;
}