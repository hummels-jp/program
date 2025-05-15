#include <iostream>

template <typename T>
class Singleton {
public:
    // 获取单例实例的静态方法
    static T& getInstance() {
        static T instance; // 静态局部变量，保证只创建一次
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符，防止复制
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    // 保护构造函数，防止直接实例化
    Singleton() = default;
    ~Singleton() = default;
};

// 示例类
class MyClass : public Singleton<MyClass> {
    friend class Singleton<MyClass>; // 允许 Singleton 访问私有构造函数
public:
    void showMessage() const {
        std::cout << "MyClass instance address: " << this << std::endl;
    }

private:
    MyClass() {
        std::cout << "MyClass instance created." << std::endl;
    }
};

int main() {
    // 获取单例实例并调用方法
    MyClass& instance1 = MyClass::getInstance();
    instance1.showMessage();

    MyClass& instance2 = MyClass::getInstance();
    instance2.showMessage();

    // 验证两个实例是否相同
    if (&instance1 == &instance2) {
        std::cout << "instance1 and instance2 are the same instance." << std::endl;
    }

    return 0;
}