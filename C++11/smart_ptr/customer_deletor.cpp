#include <iostream>
#include <memory>

// 自定义删除器
struct MyDeletor {
    void operator()(int* p) const {
        std::cout << "自定义删除器释放内存: " << *p << std::endl;
        delete p;
    }
};

int main() {
    // 使用自定义删除器的 unique_ptr
    std::unique_ptr<int, MyDeletor> up(new int(42), MyDeletor());
    std::cout << "up value: " << *up << std::endl;

    // 使用自定义删除器的 shared_ptr
    std::shared_ptr<int> sp(new int(100), MyDeletor());
    std::cout << "sp value: " << *sp << std::endl;

    return 0;
}