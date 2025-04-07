#include <vector>
#include<time.h>
#include<random>
#include<iostream>
using namespace std;

#include <chrono>
using namespace chrono;

// 生成指定数量的随机数，vector容器中的元素都是值传递到vector容器中，因此返回值用的是值传递，而不是引用传递
vector<int> generateArray(int size)
{
    vector<int> vec(size);

    // 随机数种子
    random_device rd;
    // 随机数生成器
    mt19937 gen(rd());
    // 指定随机数范围
    uniform_int_distribution<int> dis(0, 10000);
    for (int i = 0; i < size; i++)
    {
        /* code */
        vec[i] = dis(gen);
    }
    
    return vec;
}

// 性能测试
// 使用一个函数指针，指向不同的排序算法, void(*sortFunc)(vector<int>&) 参数为 vector<int>&
// vector<int> vec 为函数指针输入的参数
void testSort(const string sortName, void(*sortFunc)(vector<int>&), vector<int> vec)
{
    // 获得当前时钟
    auto start = high_resolution_clock::now();
    sortFunc(vec);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<chrono::microseconds>(end-start);

    cout << sortName << " 耗时： " << duration.count()  << " 毫秒"<< endl;
}

#include "bubble_sort.h"

int main()
{
    int size = 1000;
    vector<int> vec = generateArray(size);
    testSort("冒泡排序", bubble_sort_hqq, vec);

    return 0;
}