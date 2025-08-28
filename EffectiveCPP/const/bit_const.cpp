#include <iostream>
using namespace std;

class Demo {
private:
    int value;
    mutable int cache; // 位常量成员，允许在const成员函数中修改
public:
    Demo(int v) : value(v), cache(0) {}

    // 逻辑常量成员函数
    int getValue() const {
        cache++; // 合法，mutable成员可在const函数中修改
        return value;
    }

    // 普通成员函数
    void setValue(int v) {
        value = v;
    }

    int getCache() const {
        return cache;
    }
};

int main() {
    const Demo d(10);
    cout << "Value: " << d.getValue() << endl;      // 逻辑常量
    cout << "Cache: " << d.getCache() << endl;      // 位常量效果

    // d.setValue(20); // 编译错误，const对象不能调用非常量成员函数

    return 0;
}
