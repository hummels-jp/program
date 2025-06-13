#include <iostream>
#include <cstdint>
#include <cassert>

int main() {
    // 静态断言，判断当前系统是否为 64 位
    // static_assert(sizeof(void*) == 8, "This program requires a 64-bit system.");

    // 如果需要判断 32 位系统，可以使用以下静态断言
    // static_assert(sizeof(void*) == 4, "This program requires a 32-bit system.");

    std::cout << "System is 64-bit. Program is running." << std::endl;

    return 0;
}