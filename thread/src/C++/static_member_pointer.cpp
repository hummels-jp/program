#include <iostream>
using namespace std;

class MyClass {
public:
    static void staticFunction() {
        cout << "Static function called!" << endl;
    }
};

int main() {
    // 定义函数指针，指向返回类型为void、无参数的函数
    void (*funcPtr)();

    // 将函数指针指向类的静态成员函数
    funcPtr = &MyClass::staticFunction;

    // 调用静态成员函数
    funcPtr();

    return 0;
}