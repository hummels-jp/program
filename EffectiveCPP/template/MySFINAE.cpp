#include <type_traits>
#include <iostream>
using namespace std;


// SFINAE + enable_if 示例：只允许整数类型调用
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add(T a, T b) {
    return a + b;
}

// SFINAE + enable_if， 只允许float 函数调用
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
add (T a, T b)
{
    return a + b + 0.5;
}

int main()
{
    return 0;
}