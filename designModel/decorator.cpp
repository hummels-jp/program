#include <iostream>
#include <memory>
#include <string>

// 抽象组件类 定义接口
class Component {
public:
    virtual ~Component() = default;
    virtual void operation() const = 0;
};

// 具体组件类 实现接口
class ConcreteComponent : public Component {
public:
    void operation() const override {
        std::cout << "ConcreteComponent operation" << std::endl;
    }
};

// 抽象装饰者类 继承接口，并包含一个指向组件的指针
class Decorator : public Component {
protected:
    std::shared_ptr<Component> component;

public:
    explicit Decorator(std::shared_ptr<Component> comp) : component(std::move(comp)) {}
    void operation() const override {
        if (component) {
            component->operation();
        }
    }
};

// 具体装饰者A
class ConcreteDecoratorA : public Decorator {
public:
    explicit ConcreteDecoratorA(std::shared_ptr<Component> comp) : Decorator(std::move(comp)) {}

    void operation() const override {
        Decorator::operation();
        std::cout << "ConcreteDecoratorA additional operation" << std::endl;
    }
};

// 具体装饰者B
class ConcreteDecoratorB : public Decorator {
public:
    explicit ConcreteDecoratorB(std::shared_ptr<Component> comp) : Decorator(std::move(comp)) {}

    void operation() const override {
        Decorator::operation();
        std::cout << "ConcreteDecoratorB additional operation" << std::endl;
    }
};

int main() {
    std::shared_ptr<Component> component = std::make_shared<ConcreteComponent>();
    std::shared_ptr<Component> decoratorA = std::make_shared<ConcreteDecoratorA>(component);
    std::shared_ptr<Component> decoratorB = std::make_shared<ConcreteDecoratorB>(decoratorA);

    std::cout << "Final decorated component operation:" << std::endl;
    decoratorB->operation();

    return 0;
}