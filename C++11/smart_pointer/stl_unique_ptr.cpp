#include <iostream>
#include <memory>
using namespace std;

struct Foo {
    Foo(int v) : x(v) { cout << "Foo(" << x << ") 构造\n"; }
    ~Foo() { cout << "Foo(" << x << ") 析构\n"; }
    int x;
    void hello() { cout << "Hello, x=" << x << endl; }
};

int main() {
    // reset 用法
    unique_ptr<Foo> up1(new Foo(1));
    up1->hello();

    up1.reset(new Foo(2)); // 释放原来的Foo(1)，管理新的Foo(2)
    up1->hello();

    up1.reset(); // 释放Foo(2)，up1变为空

    // release 用法
    unique_ptr<Foo> up2(new Foo(3));
    Foo* raw = up2.release(); // up2放弃所有权，raw由用户负责释放
    if (!up2) {
        cout << "up2 已经为空\n";
    }
    raw->hello();
    delete raw; // 手动释放

    return 0;
}