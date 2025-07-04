#include <iostream>
#include <memory>
using namespace std;

// 1. 普通对象的自定义删除器
struct Foo {
    Foo() { cout << "Foo 构造\n"; }
    ~Foo() { cout << "Foo 析构\n"; }
};

void foo_deleter(Foo* p) {
    cout << "调用自定义Foo删除器\n";
    delete p;
}

// 2. 数组的自定义删除器
void int_array_deleter(int* p) {
    cout << "调用自定义int数组删除器\n";
    delete[] p;
}

int main() {
    // 1. 普通对象的 unique_ptr + 自定义删除器（函数指针）
    unique_ptr<Foo, void(*)(Foo*)> up1(new Foo, foo_deleter);

    // 2. 普通对象的 unique_ptr + 自定义删除器（lambda）
    unique_ptr<Foo, decltype([](Foo* p){ cout << "lambda删除器\n"; delete p; })>
        up2(new Foo, [](Foo* p){ cout << "lambda删除器\n"; delete p; });

    // 3. 数组的 unique_ptr + 自定义删除器
    unique_ptr<int, void(*)(int*)> up_arr(new int[5], int_array_deleter);

    // 4. 推荐：直接用 unique_ptr<T[]> 管理数组（自动用 delete[]）
    unique_ptr<int[]> up_arr2(new int[10]);
    up_arr2[0] = 42;
    cout << "up_arr2[0] = " << up_arr2[0] << endl;

    return 0;
}