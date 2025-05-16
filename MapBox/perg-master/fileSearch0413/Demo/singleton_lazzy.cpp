#include <iostream>

class Singleton {
public:
    // 获取单例实例的静态方法
    static Singleton* getInstance() {
        if (instance == nullptr) { // 如果实例不存在，则创建
            instance = new Singleton();
        }
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符，防止复制
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // 示例方法
    void showMessage() const {
        std::cout << "Singleton instance address: " << this << std::endl;
    }

private:
    // 私有构造函数，防止外部实例化
    Singleton() {
        std::cout << "Singleton instance created." << std::endl;
    }

    // 静态成员变量，存储单例实例
    static Singleton* instance;
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;

int main() {
    // 获取单例实例并调用方法
    Singleton* s1 = Singleton::getInstance();
    s1->showMessage();

    Singleton* s2 = Singleton::getInstance();
    s2->showMessage();

    // 验证两个实例是否相同
    if (s1 == s2) {
        std::cout << "s1 and s2 are the same instance." << std::endl;
    }

    return 0;
}