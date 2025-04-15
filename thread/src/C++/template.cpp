#include <iostream>
using namespace std;
/**
 * @brief 交换两个变量的值
 *
 * 该函数接受两个类型为T的引用参数，并交换它们的值。
 *
 * @param a 第一个变量
 * @param b 第二个变量
 *
 * @tparam T 变量的类型
 */
template <typename T> void mySwap(T &a, T &b) {
    // 使用临时变量temp保存变量a的值
    T temp = a;
    // 将变量b的值赋给变量a
    a = b;
    // 将临时变量temp的值赋给变量b，完成交换
    b = temp;


}

// 定义一个模板函数max_value，用于比较两个参数并返回较大的值
/**
 * @brief 返回两个值中较大的值
 *
 * 比较两个值a和b，返回其中较大的值。
 *
 * @param a 要比较的第一个值
 * @param b 要比较的第二个值
 * @return 返回a和b中较大的值
 *
 * @template T 模板类型，表示输入参数的类型
 */
template <class T> T max_value(const T &a, const T &b) { 
    // 返回a和b中较大的值
    return (a > b ? a : b); 
}

int main() {
    int i = 10;
    int j = 20;
    cout << "i=" << i << ",j=" << j << endl;
    mySwap<int>(i, j);
    cout << "i=" << i << ",j=" << j << endl;
    return 0;
}
