#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <future>

// 示例1：多线程参数传递
void thread_func(int& x) {
    x += 10;
    std::cout << "thread_func: x = " << x << std::endl;
}

// 示例2：STL算法中传递引用
void add_one(int& n) {
    n += 1;
}

// 示例3：std::bind 绑定引用参数
void print_ref(int& y) {
    y *= 2;
    std::cout << "print_ref: y = " << y << std::endl;
}

// 示例4：std::function 包装引用参数
void show(int& z) {
    z -= 3;
    std::cout << "show: z = " << z << std::endl;
}

// 示例5：std::async 传递引用
void async_func(int& a) {
    a += 100;
    std::cout << "async_func: a = " << a << std::endl;
}

// 示例6：容器中存储引用
void container_example() {
    int m = 1, n = 2;
    std::vector<std::reference_wrapper<int>> refs = {std::ref(m), std::ref(n)};
    refs[0].get() += 10;
    refs[1].get() += 20;
    std::cout << "container_example: m = " << m << ", n = " << n << std::endl;
}

int main() {
    // 1. 多线程参数传递
    int x = 5;
    std::thread t1(thread_func, std::ref(x));
    t1.join();
    std::cout << "main: x = " << x << std::endl;

    // 2. STL算法中传递引用
    std::vector<int> v{1, 2, 3};
    std::for_each(v.begin(), v.end(), add_one);
    std::cout << "main: v = ";
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;

    // 3. std::bind 绑定引用参数
    int y = 7;
    auto f = std::bind(print_ref, std::ref(y));
    f();
    std::cout << "main: y = " << y << std::endl;

    // 4. std::function 包装引用参数
    int z = 20;
    std::function<void()> func = std::bind(show, std::ref(z));
    func();
    std::cout << "main: z = " << z << std::endl;

    // 5. std::async 传递引用
    int a = 1;
    auto fut = std::async(async_func, std::ref(a));
    fut.get();
    std::cout << "main: a = " << a << std::endl;

    // 6. 容器中存储引用
    container_example();

    return 0;
}