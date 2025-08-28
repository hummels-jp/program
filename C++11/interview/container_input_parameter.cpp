#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Foo {
    Foo() { cout << "default ctor\n"; }
    Foo(const Foo&) { cout << "copy ctor\n"; }
    Foo(Foo&&) noexcept { cout << "move ctor\n"; }
};

int main() {
    vector<Foo> v;
    Foo a;
    v.push_back(a);           // 左值，调用拷贝构造函数
    v.push_back(Foo());       // 右值，调用移动构造函数
    v.push_back(std::move(a));// 右值，调用移动构造函数
    return 0;
}