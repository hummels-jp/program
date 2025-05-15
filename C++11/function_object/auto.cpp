#include <iostream>
#include <vector>
using namespace std;

int add(int x, int y) { return x + y; }

int main() {

    int a = 1;
    double b = 2.0;
    float c = 3.0f;  
    long double d = 4.0L;
    const char* e = "hello";

    // 不使用 auto，声明函数指针
    int (*func_ptr)(int, int) = add;
    cout << "add(3, 5) = " << func_ptr(3, 5) << endl;

    // 使用 auto，声明函数指针
    auto func_ptr_auto = add;
    cout << "add(7, 9) = " << func_ptr_auto(7, 9) << endl;

    return 0;
}