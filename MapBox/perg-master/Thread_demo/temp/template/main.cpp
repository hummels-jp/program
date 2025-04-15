#include "parameter_pack.h"

int main() {
    // 测试递归展开的参数包模板函数
    printArgs(1, 2.5, "Hello", 'A'); // 打印多个不同类型的参数

    // 测试使用折叠表达式的参数包模板函数
    printArgsWithFold(1, 2.5, "Hello", 'A'); // 打印多个不同类型的参数
    printArgsWithFold("Parameter pack", 42, 3.14); // 打印字符串、整数和浮点数

    return 0;
}