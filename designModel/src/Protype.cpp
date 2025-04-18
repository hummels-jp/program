#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

// 原型接口
class Prototype {
public:
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void printDetails() const = 0;
    virtual ~Prototype() = default;
};

// 具体原型类：Circle
class Circle : public Prototype {
private:
    int radius;

public:
    Circle(int r) : radius(r) {}

    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<Circle>(*this); // 深拷贝
    }

    void printDetails() const override {
        std::cout << "Circle with radius: " << radius << std::endl;
    }
};

// 具体原型类：Rectangle
class Rectangle : public Prototype {
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<Rectangle>(*this); // 深拷贝
    }

    void printDetails() const override {
        std::cout << "Rectangle with width: " << width << " and height: " << height << std::endl;
    }
};

// 原型工厂
class PrototypeFactory {
private:
    std::unordered_map<std::string, std::unique_ptr<Prototype>> prototypes;

public:
    void registerPrototype(const std::string& key, std::unique_ptr<Prototype> prototype) {
        prototypes[key] = std::move(prototype);
    }

    std::unique_ptr<Prototype> createPrototype(const std::string& key) const {
        if (prototypes.find(key) != prototypes.end()) {
            return prototypes.at(key)->clone();
        }
        throw std::runtime_error("Prototype not found!");
    }
};

// 客户端代码
int main() {
    PrototypeFactory factory;

    // 注册原型
    factory.registerPrototype("circle", std::make_unique<Circle>(10));
    factory.registerPrototype("rectangle", std::make_unique<Rectangle>(20, 30));

    // 创建对象
    auto circle = factory.createPrototype("circle");
    circle->printDetails();

    auto rectangle = factory.createPrototype("rectangle");
    rectangle->printDetails();

    return 0;
}