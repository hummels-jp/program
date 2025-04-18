#include <iostream>
#include <memory>
#include <string>

// 饮料基类
class Beverage {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Beverage() = default;
};

// 具体饮料：咖啡
class Coffee : public Beverage {
public:
    std::string getDescription() const override {
        return "Coffee";
    }

    double cost() const override {
        return 5.0; // 咖啡的基础价格
    }
};

// 装饰者基类
class BeverageDecorator : public Beverage {
protected:
    std::shared_ptr<Beverage> beverage;

public:
    explicit BeverageDecorator(std::shared_ptr<Beverage> bev) : beverage(std::move(bev)) {}
};

// 具体装饰者：加糖
class SugarDecorator : public BeverageDecorator {
public:
    explicit SugarDecorator(std::shared_ptr<Beverage> bev) : BeverageDecorator(std::move(bev)) {}

    std::string getDescription() const override {
        return beverage->getDescription() + ", Sugar";
    }

    double cost() const override {
        return beverage->cost() + 0.5; // 加糖的额外费用
    }
};

// 具体装饰者：加牛奶
class MilkDecorator : public BeverageDecorator {
public:
    explicit MilkDecorator(std::shared_ptr<Beverage> bev) : BeverageDecorator(std::move(bev)) {}

    std::string getDescription() const override {
        return beverage->getDescription() + ", Milk";
    }

    double cost() const override {
        return beverage->cost() + 1.0; // 加牛奶的额外费用
    }
};

// 客户端代码
int main() {
    // 创建基础饮料：咖啡
    std::shared_ptr<Beverage> beverage = std::make_shared<Coffee>();
    std::cout << beverage->getDescription() << " costs $" << beverage->cost() << "\n";

    // 加糖
    beverage = std::make_shared<SugarDecorator>(beverage);
    std::cout << beverage->getDescription() << " costs $" << beverage->cost() << "\n";

    // 加牛奶
    beverage = std::make_shared<MilkDecorator>(beverage);
    std::cout << beverage->getDescription() << " costs $" << beverage->cost() << "\n";

    return 0;
}