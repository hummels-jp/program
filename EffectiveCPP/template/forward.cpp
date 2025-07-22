#include <iostream>
#include <utility>
using namespace std;

// 普通函数，打印左值/右值
void print(int& x) { cout << "左值: " << x << endl; }
void print(int&& x) { cout << "右值: " << x << endl; }

// 完美转发模板
template<typename T>
void wrapper(T&& arg) {
    print(arg); // 不能保持参数原来的左值/右值属性
    print(std::forward<T>(arg)); // 保持参数原来的左值/右值属性
}

int main() {
    int a = 10;
    wrapper(a);        // 输出 左值: 10
    wrapper(20);       // 输出 右值: 20
    return 0;
}