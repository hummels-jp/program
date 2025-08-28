#include <iostream>
using namespace std;

// 普通静态局部变量示例
void foo() {
    static int count = 0; // 只初始化一次，所有调用共享
    count++;
    cout << "foo count: " << count << endl;
}

// inline static 类成员变量示例（C++17及以上）
class Bar {
public:
    inline static int value = 100; // 可在类内直接初始化
    void show() { cout << "Bar value: " << value << endl; }
};

int main() {
    foo();
    foo();

    Bar b1, b2;
    b1.show();
    Bar::value++;
    b2.show();

    return 0;
}