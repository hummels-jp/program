#include <iostream>
using namespace std;

int g1;
int g2 = 0;
int g3 = 1;
int g4 = 2;

static int g5; // 未初始化，自动初始化为0
static int g6 = 0; // 静态变量，初始化为0
static int g7 = 3; // 静态变量，初始化为3

int main()
{
    // cout << "code zone " <<  main  << endl;

    // cout << "g1" << &g1 << endl;
    // cout << "g2" << &g2 << endl;
    // cout << "g3" << &g3 << endl;
    // cout << "g4" << &g4 << endl;

    // cout << "g5" << &g5 << endl;
    // cout << "g6" << &g6 << endl;
    // cout << "g7" << &g7 << endl;

    int arr[10] = {0}; // 栈上分配的数组
    cout << sizeof(arr) << endl; // 输出数组大小
    for (int i = 0; i < 10; i++)
    {
        /* code */
        cout << arr[i] << " "; // 输出数组元素，未初始化的数组元素值不确定
    }
    cout << endl;

    int * arr2 = new int[10]; // 动态分配的数组
    for (int i = 0; i < 10; i++) {
        arr2[i] = 1; // 全部初始化为1
    }
    // 不能使用 foreach（范围for）访问堆空间数组，只能用下标
    for (int i = 0; i < 10; i++)
    {
        cout << arr2[i] << " "; // 正确：用下标访问
    }
    cout << endl;
    // 错误示例：不能这样写
    // for (auto x : arr2) { cout << x << " "; } // 错误：不能对动态分配的数组使用范围for
    // for (auto x : arr2) { cout << x << " "; }
    cout << sizeof(arr2) << endl; // 输出指针大小，而不是数组大小
    delete[] arr2; // 释放动态分配的内存
    arr2 = nullptr; // 避免悬空指针
}