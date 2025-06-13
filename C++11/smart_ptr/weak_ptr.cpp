#include <iostream>
#include <memory>

int main() {
    // 创建一个 shared_ptr
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(42);

    // 使用 shared_ptr 初始化 weak_ptr
    std::weak_ptr<int> weakPtr(sharedPtr);

    // 检查 weak_ptr 是否有效
    if (auto lockedPtr = weakPtr.lock()) { // 尝试锁定 weak_ptr
        std::cout << "weak_ptr 有效，值为: " << *lockedPtr << std::endl;
    } else {
        std::cout << "weak_ptr 无效" << std::endl;
    }

    // 重置 shared_ptr
    // sharedPtr.reset();

    // 通过 lock 获得 shared_ptr
    std::shared_ptr<int> newSharedPtr = weakPtr.lock();
    if (newSharedPtr) {
        std::cout << "通过 lock 获得 shared_ptr，值为: " << *newSharedPtr << std::endl;
    } else {
        std::cout << "无法通过 lock 获得 shared_ptr" << std::endl;
    }

    std::cout << weakPtr.use_count() << std::endl; // weak_ptr 的引用计数为 1

    // 再次检查 weak_ptr 是否有效
    if (auto lockedPtr = weakPtr.lock()) {
        std::cout << "weak_ptr 有效，值为: " << *lockedPtr << std::endl;
    } else {
        std::cout << "weak_ptr 无效" << std::endl;
    }

    return 0;
}