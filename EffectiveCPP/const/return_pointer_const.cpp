#include <iostream>
using namespace std;

class Demo {
private:
    int value;
    mutable int cache; // mutable成员变量，可在const成员函数中修改
public:
    Demo(int v) : value(v), cache(0) {}

    // 返回非常量指针
    int* getPtr() {
        return &value;
    }

    // 返回常量指针
    const int* getConstPtr() const {
        return &value;
    }

    // 逻辑常量成员函数
    int getValue() const {
        cache++; // 合法，mutable成员可在const函数中修改
        return value;
    }

    int getCache() const {
        return cache;
    }
};

int main() {
    Demo d(10);

    // 非const指针，可以通过指针修改成员变量
    *d.getPtr() = 20;
    cout << "After modify: " << *d.getPtr() << endl;

    // const指针，只能读取，不能修改
    const Demo d2(30);
    cout << "Const pointer value: " << *d2.getConstPtr() << endl;

    // *d2.getConstPtr() = 40; // 编译错误，不能通过const指针修改

    // 逻辑常量与mutable演示
    cout << "d2.getValue(): " << d2.getValue() << endl;
    cout << "d2.getCache(): " << d2.getCache() << endl;

    return 0;
}
