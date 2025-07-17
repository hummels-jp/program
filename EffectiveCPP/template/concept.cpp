#include <iostream>
using namespace std;

// C++20 concept 关键字示例：约束类型必须可加法
template<typename T>
concept Addable = requires(T a, T b) 
{
    { a + b } -> std::convertible_to<T>;
};

// 使用 concept 约束模板参数
template<Addable T>
T add(T a, T b) {
    return a + b;
}

// SFINAE 示例（C++11/14/17风格）
#include <type_traits>
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add_int(T a, T b) {
    return a + b;
}

int main() {
    cout << add(1, 2) << endl;           // concept约束，输出3
    cout << add(1.5, 2.5) << endl;       // concept约束，输出4
    // cout << add("a", "b") << endl;    // 编译错误，不满足Addable

    cout << add_int(10, 20) << endl;     // SFINAE约束，只允许整数
    // cout << add_int(1.5, 2.5) << endl; // 编译错误，SFINAE屏蔽
    return 0;
}