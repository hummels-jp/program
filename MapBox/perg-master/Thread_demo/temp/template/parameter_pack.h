#pragma once
#include <iostream>

// 基础模板：递归终止条件
void printArgs() {
    std::cout << std::endl; // 打印换行
}

// 可变参数模板函数：递归展开参数包
template <typename T, typename... Args>
void printArgs(T first, Args... rest) {
    std::cout << first << " "; // 打印当前参数
    printArgs(rest...);        // 递归调用，展开剩余参数
}

// 使用折叠表达式的模板函数
template <typename... Args>
void printArgsWithFold(Args... args) {
    (std::cout << ... << args) << std::endl; // 使用折叠表达式打印所有参数
}