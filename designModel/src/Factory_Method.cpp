#include <iostream>
#include <memory>

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

// 工厂基类
class Creator {
public:
    virtual std::unique_ptr<Product> createProduct() const = 0;
    virtual ~Creator() = default;
};

// 具体工厂A
class ConcreteCreatorA : public Creator {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<ConcreteProductA>();
    }
};

// 具体工厂B
class ConcreteCreatorB : public Creator {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<ConcreteProductB>();
    }
};

// 客户端代码
void clientCode(const Creator& creator) {
    auto product = creator.createProduct();
    product->use();
}

int main() {
    std::cout << "App: Launched with ConcreteCreatorA." << std::endl;
    ConcreteCreatorA creatorA;
    clientCode(creatorA);

    std::cout << "App: Launched with ConcreteCreatorB." << std::endl;
    ConcreteCreatorB creatorB;
    clientCode(creatorB);

    return 0;
}