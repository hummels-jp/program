#include <iostream>
#include <memory>
#include <string>

// 抽象产品类
class Product {
public:
    virtual void use() const = 0;
    virtual ~Product() = default;
};

// 具体产品A
class ConcreteProductA : public Product {
public:
    void use() const override {
        std::cout << "Using Product A" << std::endl;
    }
};

// 具体产品B
class ConcreteProductB : public Product {
public:
    void use() const override {
        std::cout << "Using Product B" << std::endl;
    }
};

// 简单工厂类
class SimpleFactory {
public:
    static std::unique_ptr<Product> createProduct(const std::string& type) {
        if (type == "A") {
            return std::make_unique<ConcreteProductA>();
        } else if (type == "B") {
            return std::make_unique<ConcreteProductB>();
        } else {
            return nullptr;
        }
    }
};

// 客户端代码
int main() {
    std::cout << "App: Requesting Product A." << std::endl;
    auto productA = SimpleFactory::createProduct("A");
    if (productA) {
        productA->use();
    }

    std::cout << "App: Requesting Product B." << std::endl;
    auto productB = SimpleFactory::createProduct("B");
    if (productB) {
        productB->use();
    }

    std::cout << "App: Requesting an unknown product." << std::endl;
    auto unknownProduct = SimpleFactory::createProduct("C");
    if (!unknownProduct) {
        std::cout << "Unknown product type!" << std::endl;
    }

    return 0;
}