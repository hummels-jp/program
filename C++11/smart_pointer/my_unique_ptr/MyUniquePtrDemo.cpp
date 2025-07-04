#include <iostream>
#include "MyUniquePtr.h"
using namespace std;

// 示例
struct Foo {
    Foo() { cout << "Foo 构造\n"; }
    ~Foo() { cout << "Foo 析构\n"; }
    void hello() { cout << "Hello from Foo\n"; }
};

int main()
{
    MyUniquePtr<Foo> p1(new Foo);
    p1->hello();

    MyUniquePtr<Foo> p2 = std::move(p1);
    if (!p1)
    {
        cout << "p1 loose ownership " << endl; 
    }
    if (p2)
    {
        cout << "p2 get ownership " << endl;
        p2->hello();
    }

    // 将智能指针指向新的资源
    p2.reset(new Foo());
    p2->hello();

    // 将智能指针的资源释放
    Foo* f = p2.release();
    if (!p2)
    {
        cout << "p2 loose ownership " << endl;
    }
    f->hello();
    delete f;

    return 0;
}