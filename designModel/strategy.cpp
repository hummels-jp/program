#include <iostream>
#include <memory>

// 策略接口
class Strategy {
public:
    virtual void execute() const = 0;
    virtual ~Strategy() = default;
};

// 具体策略A
class ConcreteStrategyA : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy A" << std::endl;
    }
};

// 具体策略B
class ConcreteStrategyB : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy B" << std::endl;
    }
};

// 上下文类
class Context {
private:
    std::unique_ptr<Strategy> strategy;

public:
    void setStrategy(std::unique_ptr<Strategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    void executeStrategy() const {
        if (strategy) {
            strategy->execute();
        } else {
            std::cout << "No strategy set" << std::endl;
        }
    }
};

int main() {
    Context context;

    // 使用策略A
    context.setStrategy(std::make_unique<ConcreteStrategyA>());
    context.executeStrategy();

    // 使用策略B
    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.executeStrategy();

    return 0;
}