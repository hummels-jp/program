#include <iostream>
#include <utility>
using namespace std;

struct Foo {
    Foo() { cout << "default ctor\n"; }
    Foo(const Foo&) { cout << "copy ctor\n"; }
    Foo(Foo&&) noexcept { cout << "move ctor\n"; }
};

void bar(const Foo& f) {
    cout << "bar(const Foo&) called\n";
}
void bar(Foo&& f) {
    cout << "bar(Foo&&) called\n";
}

template<typename T>
void wrapper(T&& arg) {
    // 完美转发，保留参数的左值/右值属性
    bar(std::forward<T>(arg));
}

int main() {
    Foo foo;
    wrapper(foo);            // 左值，调用 bar(const Foo&)
    wrapper(std::move(foo)); // 右值，调用 bar(Foo&&)
    return 0;
}