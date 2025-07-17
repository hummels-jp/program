#include <iostream>
using namespace std;

// 1维折叠表达式示例（C++17及以上）
template<typename... Args>
auto sum(Args... args) {
    return (args + ...); // 从左到右折叠
}

int main() {
    cout << sum(1, 2, 3, 4) << endl;         // 输出 10
    cout << sum(1.5, 2.5, 3.5) << endl;      // 输出 7.5
    cout << sum(100) << endl;                // 输出 100
    return 0;
}