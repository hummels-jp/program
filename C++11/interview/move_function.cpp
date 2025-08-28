#include <iostream>
#include <utility>
using namespace std;

struct Foo {
    Foo() { cout << "default ctor\n"; }
    Foo(const Foo&) { cout << "copy ctor\n"; }
    Foo(Foo&&) noexcept { cout << "move ctor\n"; }
};

void bar(Foo& f)
{
    cout << "bar(Foo& f) called " << endl;
}

void bar(Foo&& f) {
    cout << "bar(Foo&& f) called\n";
}

void wrapper(Foo&& f) {
    // 直接传递f，会变成左值，调用拷贝构造
    bar(f);            // 拷贝构造
    // 使用std::move(f)，保持右值属性，调用移动构造
    bar(std::move(f)); // 移动构造
}

int main() {
    Foo foo;
    wrapper(std::move(foo));
    return 0;
}