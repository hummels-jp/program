#include <iostream>
#include <type_traits>
using namespace std;

// SFINAE + enable_if 示例：只允许整数类型调用
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add(T a, T b) {
    return a + b;
}

// SFINAE + enable_if 示例：只允许浮点类型调用
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
add(T a, T b) {
    return a + b + 0.5; // 演示不同实现
}

int main() {
    cout << add(1, 2) << endl;      // 输出 3（整数版本）
    cout << add(1.5, 2.5) << endl;  // 输出 4.5（浮点版本）
    // cout << add("a", "b") << endl; // 编译错误，SFINAE屏蔽
    return 0;
}