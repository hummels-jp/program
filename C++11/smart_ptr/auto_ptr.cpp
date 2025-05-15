#include <iostream>
#include <memory> // 包含 unique_ptr

int main() {
    std::unique_ptr<int> p1(new int(10)); // 创建 unique_ptr，管理 int 指针
    std::cout << "p1: " << *p1 << std::endl;

    // 转移所有权
    std::unique_ptr<int> p2 = std::move(p1);
    if (p1.get() == nullptr) {
        std::cout << "p1 现在为空" << std::endl;
    }
    std::cout << "p2: " << *p2 << std::endl;

    return 0;
}