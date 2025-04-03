#include <iostream>
#include <memory>
#include <string>

// 实现部分接口
class Color {
public:
    virtual ~Color() = default;
    virtual std::string getColor() const = 0;
};

class Red : public Color {
public:
    std::string getColor() const override {
        return "Red";
    }
};

class Blue : public Color {
public:
    std::string getColor() const override {
        return "Blue";
    }
};

// 抽象部分接口
class Shape {
protected:
    std::shared_ptr<Color> color;
public:
    Shape(std::shared_ptr<Color> c) : color(c) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    Circle(std::shared_ptr<Color> c) : Shape(c) {}
    void draw() const override {
        std::cout << "Drawing a " << color->getColor() << " Circle." << std::endl;
    }
};

class Rectangle : public Shape {
public:
    Rectangle(std::shared_ptr<Color> c) : Shape(c) {}
    void draw() const override {
        std::cout << "Drawing a " << color->getColor() << " Rectangle." << std::endl;
    }
};

int main() {
    std::shared_ptr<Color> red = std::make_shared<Red>();
    std::shared_ptr<Color> blue = std::make_shared<Blue>();

    std::shared_ptr<Shape> redCircle = std::make_shared<Circle>(red);
    std::shared_ptr<Shape> blueRectangle = std::make_shared<Rectangle>(blue);

    redCircle->draw();
    blueRectangle->draw();

    return 0;
}