#include <iostream>
#include <memory>
#include <string>

// 策略接口，定义税率计算方法
class TaxStrategy {
public:
    virtual double calculateTax(double amount) const = 0;
    virtual ~TaxStrategy() = default;
};

// 英国税率策略
class UKTaxStrategy : public TaxStrategy {
public:
    double calculateTax(double amount) const override {
        return amount * 0.2; // 20% 税率
    }
};

// 美国税率策略
class USTaxStrategy : public TaxStrategy {
public:
    double calculateTax(double amount) const override {
        return amount * 0.1; // 10% 税率
    }
};

// 日本税率策略
class JapanTaxStrategy : public TaxStrategy {
public:
    double calculateTax(double amount) const override {
        return amount * 0.08; // 8% 税率
    }
};

// SalesOrder 类，使用策略模式计算税率
class SalesOrder {
private:
    std::unique_ptr<TaxStrategy> taxStrategy;

public:
    // 设置税率策略
    void setTaxStrategy(std::unique_ptr<TaxStrategy> strategy) {
        taxStrategy = std::move(strategy);
    }

    // 计算总价（含税）
    double calculateTotal(double amount) const {
        if (!taxStrategy) {
            throw std::runtime_error("Tax strategy is not set.");
        }
        double tax = taxStrategy->calculateTax(amount);
        return amount + tax;
    }
};

// 客户端代码
int main() {
    SalesOrder order;

    // 使用英国税率策略
    order.setTaxStrategy(std::make_unique<UKTaxStrategy>());
    std::cout << "Total with UK tax: " << order.calculateTotal(100.0) << "\n";

    // 使用美国税率策略
    order.setTaxStrategy(std::make_unique<USTaxStrategy>());
    std::cout << "Total with US tax: " << order.calculateTotal(100.0) << "\n";

    // 使用日本税率策略
    order.setTaxStrategy(std::make_unique<JapanTaxStrategy>());
    std::cout << "Total with Japan tax: " << order.calculateTotal(100.0) << "\n";

    return 0;
}