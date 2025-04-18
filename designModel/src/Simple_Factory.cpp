#include <iostream>
#include <memory>
#include <string>

// 枚举类型，用于标识产品类型
enum class ProductType {
    ProductA,
    ProductB,
    Unknown
};

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
    // 创建产品的静态方法，根据传入的类型返回相应的产品实例
    static std::unique_ptr<Product> createProduct(ProductType type) {
        switch (type) {
        case ProductType::ProductA:
            return std::make_unique<ConcreteProductA>();
        case ProductType::ProductB:
            return std::make_unique<ConcreteProductB>();
        default:
            return nullptr;
        }
    }
};

// 客户端代码
int main() {
    std::cout << "App: Requesting Product A." << std::endl;
    auto productA = SimpleFactory::createProduct(ProductType::ProductA);
    if (productA) {
        productA->use();
    }

    std::cout << "App: Requesting Product B." << std::endl;
    auto productB = SimpleFactory::createProduct(ProductType::ProductB);
    if (productB) {
        productB->use();
    }

    std::cout << "App: Requesting an unknown product." << std::endl;
    auto unknownProduct = SimpleFactory::createProduct(ProductType::Unknown);
    if (!unknownProduct) {
        std::cout << "Unknown product type!" << std::endl;
    }

    return 0;
}