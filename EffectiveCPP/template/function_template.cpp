#include <iostream>
using namespace std;

// 普通函数模板
template<typename T>
T add(T a, T b) {
    return a + b;
}

// 全特化：当类型为 const char* 时，拼接字符串
template<>
const char* add<const char*>(const char* a, const char* b) {
    static string result; // 注意：返回局部静态变量指针，仅用于演示
    result = string(a) + string(b);
    return result.c_str();
}

int main() {
    cout << add(1, 2) << endl;                // 输出 3
    cout << add(1.5, 2.5) << endl;            // 输出 4
    cout << add<string>("abc", "def") << endl;// 输出 abcdef
    cout << add<const char*>("hello", "world") << endl; // 输出 helloworld
    return 0;
}