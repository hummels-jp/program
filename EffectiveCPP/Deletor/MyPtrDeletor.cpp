
#include<memory>
#include <iostream>
#include <functional>
using namespace std;

// 1. 普通对象的自定义删除器
struct Foo {
    Foo() { cout << "Foo 构造\n"; }
    ~Foo() { cout << "Foo 析构\n"; }
};

// 2 定义普通函数
void foo_deletor(Foo* p)
{
    cout << " foo_deletor " << endl;
    delete p;
}

// 3 使用仿函数作为Deletor
struct FooDeletor
{
    void operator()(Foo* p) const
    {
        cout << "FooDeletor deletor " << endl;
        delete p;
    }
};

int main()
{
    // unique_ptr<Foo> up1(new Foo);

    // unique_ptr<Foo, void(*)(Foo*)> up2(new Foo, foo_deletor);

    // unique_ptr<Foo, FooDeletor> up3(new Foo, FooDeletor{});

    auto lambda_deletor = [](Foo* p)->void
    {
        cout << "lambda_deletor " << endl;
        delete p;
    };

    unique_ptr<Foo, decltype(lambda_deletor)> up4(new Foo, lambda_deletor);
    
}