#include <iostream>
using namespace std;

class Demo {
private:
    int value;
public:
    Demo(int v) : value(v) {}

    // 返回非常量引用
    int& getValue() {
        return value;
    }

    // 返回常量引用
    const int& getConstValue() const {
        return value;
    }
};

int main() {
    Demo d(10);

    // 非const引用，可以修改成员变量
    d.getValue() = 20;
    cout << "After modify: " << d.getValue() << endl;

    // const引用，只能读取，不能修改
    const Demo d2(30);
    cout << "Const value: " << d2.getConstValue() << endl;

    // d2.getConstValue() = 40; // 编译错误，不能通过const引用修改

    return 0;
}
