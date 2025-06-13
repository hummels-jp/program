#include <iostream>

// 局部静态变量用来保存状态
void foo() {
    static int count = 0; // 局部静态对象，只初始化一次
    count++;
    std::cout << "foo called " << count << " times" << std::endl;
}

// 局部静态对象用来实现单例模式
// 单例模式：确保一个类只有一个实例，并提供一个全局访问点
class Priest {
public:
    static Priest& getInstance() {
        static Priest instance;
        return instance;
    }
    void pray() {
        std::cout << "Priest is praying." << std::endl;
    }
private:
    Priest()
    {
        std::cout << "Priest created." << std::endl;
    };
    Priest(const Priest&) = delete;
    Priest& operator=(const Priest&) = delete;
};

// 局部静态变量用来保存递归的中间状态
int factorial(int n) {
    static int result = 1;
    // 递归计算阶乘 
    // 这里使用了局部静态变量来保存中间结果
    if (n == 0 || n == 1) {
        int temp = result;
        result = 1; // reset for next call
        return temp;
    }

    // 计算阶乘
    result *= n;
    int temp = factorial(n - 1);

    // 递归结束后，result保存了n的阶乘
    if (n == 2) result = 1; // reset for next call
    return temp;
}

int main() {
    // 局部静态变量用来保存状态
    for (int i = 0; i < 5; ++i) {
        foo();
    }

    // 局部静态对象用来实现单例模式
    Priest& priest = Priest::getInstance();

    // 局部对象用来保存递归的中间状态
    std::cout << "Factorial of 5: " << factorial(5) << std::endl;
    
    return 0;
}