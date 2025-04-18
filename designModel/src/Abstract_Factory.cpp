#include <iostream>
#include <memory>

// 抽象产品A
class AbstractProductA {
public:
    virtual void use() const = 0;
    virtual ~AbstractProductA() = default;
};

// 抽象产品B
class AbstractProductB {
public:
    virtual void use() const = 0;
    virtual ~AbstractProductB() = default;
};

// 具体产品A1
class ConcreteProductA1 : public AbstractProductA {
public:
    void use() const override {
        std::cout << "Using Product A1" << std::endl;
    }
};

// 具体产品A2
class ConcreteProductA2 : public AbstractProductA {
public:
    void use() const override {
        std::cout << "Using Product A2" << std::endl;
    }
};

// 具体产品B1
class ConcreteProductB1 : public AbstractProductB {
public:
    void use() const override {
        std::cout << "Using Product B1" << std::endl;
    }
};

// 具体产品B2
class ConcreteProductB2 : public AbstractProductB {
public:
    void use() const override {
        std::cout << "Using Product B2" << std::endl;
    }
};

// 抽象工厂
class AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::unique_ptr<AbstractProductB> createProductB() const = 0;
    virtual ~AbstractFactory() = default;
};

// 具体工厂1
class ConcreteFactory1 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        return std::make_unique<ConcreteProductA1>();
    }

    std::unique_ptr<AbstractProductB> createProductB() const override {
        return std::make_unique<ConcreteProductB1>();
    }
};

// 具体工厂2
class ConcreteFactory2 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        return std::make_unique<ConcreteProductA2>();
    }

    std::unique_ptr<AbstractProductB> createProductB() const override {
        return std::make_unique<ConcreteProductB2>();
    }
};

// 客户端代码
void clientCode(const AbstractFactory& factory) {
    auto productA = factory.createProductA();
    auto productB = factory.createProductB();
    productA->use();
    productB->use();
}

int main() {
    std::cout << "App: Using ConcreteFactory1." << std::endl;
    ConcreteFactory1 factory1;
    clientCode(factory1);

    std::cout << "App: Using ConcreteFactory2." << std::endl;
    ConcreteFactory2 factory2;
    clientCode(factory2);

    return 0;
}