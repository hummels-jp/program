#include <iostream>
// 使用静态局部变量递归求斐波那契数列，避免重复计算
int fiona(int n) {
    static int cache[100] = {0}; // 假设n不超过99
    if (n == 0 || n == 1) return 1;
    if (cache[n] != 0) return cache[n];
    cache[n] = fiona(n - 1) + fiona(n - 2);
    return cache[n];
}

int fiona(int n){
    if (n == 0 || n == 1) return 1;
    return fiona(n - 1) + fiona(n - 2);
}

int main() {
    int n = 5;
    std::cout << "Fiona of " << n << ": " << fiona(n) << std::endl;
    return 0;
}