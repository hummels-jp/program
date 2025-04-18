#include <iostream>

// 抽象基类，定义模板方法
class AbstractClass {
public:
    // 模板方法，定义算法的骨架
    void templateMethod() const {
        baseOperation1();
        requiredOperation1();
        baseOperation2();
        requiredOperation2();
        hook();
    }

    // 基本操作，提供默认实现
    void baseOperation1() const {
        std::cout << "AbstractClass: Base Operation 1\n";
    }

    void baseOperation2() const {
        std::cout << "AbstractClass: Base Operation 2\n";
    }

    // 必须由子类实现的抽象操作
    virtual void requiredOperation1() const = 0;
    virtual void requiredOperation2() const = 0;

    // 钩子方法，子类可以选择性地重写
    virtual void hook() const {}
    
    virtual ~AbstractClass() = default;
};

// 具体类A
class ConcreteClassA : public AbstractClass {
protected:
    void requiredOperation1() const override {
        std::cout << "ConcreteClassA: Implemented Operation 1\n";
    }

    void requiredOperation2() const override {
        std::cout << "ConcreteClassA: Implemented Operation 2\n";
    }
};

// 具体类B
class ConcreteClassB : public AbstractClass {
protected:
    void requiredOperation1() const override {
        std::cout << "ConcreteClassB: Implemented Operation 1\n";
    }

    void requiredOperation2() const override {
        std::cout << "ConcreteClassB: Implemented Operation 2\n";
    }

    void hook() const override {
        std::cout << "ConcreteClassB: Overridden Hook\n";
    }
};

// 客户端代码
void clientCode(const AbstractClass& obj) {
    obj.templateMethod();
}

int main() {
    std::cout << "Client: Using ConcreteClassA:\n";
    ConcreteClassA concreteA;
    clientCode(concreteA);

    std::cout << "\nClient: Using ConcreteClassB:\n";
    ConcreteClassB concreteB;
    clientCode(concreteB);

    return 0;
}