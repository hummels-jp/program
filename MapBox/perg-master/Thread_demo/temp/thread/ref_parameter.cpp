#include <iostream>
#include <thread>

void modify(int& x) {
    x += 10;
    std::cout << "In thread: x = " << x << std::endl;
}

int main() {
    int value = 5;

    std::thread t(modify, std::ref(value)); // 👈 使用 std::ref 传引用
    t.join();

    std::cout << "In main: x = " << value << std::endl; // 修改生效
    return 0;
}
