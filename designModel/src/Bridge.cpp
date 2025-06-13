#include <iostream>
#include <memory>
#include <string>

// 实现部分：颜色接口
class Color {
public:
    virtual std::string getColor() const = 0;
    virtual ~Color() = default;
};

// 具体颜色：红色
class Red : public Color {
public:
    std::string getColor() const override {
        return "Red";
    }
};

// 具体颜色：蓝色
class Blue : public Color {
public:
    std::string getColor() const override {
        return "Blue";
    }
};

// 抽象部分：形状接口
class Shape {
protected:
    std::shared_ptr<Color> color;

public:
    explicit Shape(std::shared_ptr<Color> c) : color(std::move(c)) {}
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// 具体形状：圆形
class Circle : public Shape {
public:
    explicit Circle(std::shared_ptr<Color> c) : Shape(std::move(c)) {}

    void draw() const override {
        std::cout << "Drawing a " << color->getColor() << " Circle" << std::endl;
    }
};

// 具体形状：矩形
class Rectangle : public Shape {
public:
    explicit Rectangle(std::shared_ptr<Color> c) : Shape(std::move(c)) {}

    void draw() const override {
        std::cout << "Drawing a " << color->getColor() << " Rectangle" << std::endl;
    }
};

// 客户端代码
int main() {
    // 创建红色和蓝色
    auto red = std::make_shared<Red>();
    auto blue = std::make_shared<Blue>();

    // 创建不同颜色的形状
    auto redCircle = std::make_shared<Circle>(red);
    auto blueRectangle = std::make_shared<Rectangle>(blue);

    // 绘制形状
    redCircle->draw();
    blueRectangle->draw();

    return 0;
}