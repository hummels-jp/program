#include <iostream>

// 使用静态局部变量递归求阶乘，避免重复计算
int factorial(int n) {
    static int cache[100] = {0}; // 假设n不超过99
    if (n == 0 || n == 1) return 1;
    if (cache[n] != 0) return cache[n];
    cache[n] = n * factorial(n - 1);
    return cache[n];
}

// 使用递归计算阶乘
int factorial2(int n){
    if (n == 0 || n == 1) return 1;
    return n * factorial2(n - 1);
}

int main() {

    int n = 5;
    std::cout << "Factorial of " << n << " using static local variable: " << factorial(n) << std::endl;
    std::cout << "Factorial of " << n << " using recursion: " << factorial2(n) << std::endl;
    return 0;
}