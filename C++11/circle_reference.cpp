#include <iostream>
 #include <memory>
#include <string>
using namespace std;

class Point : public std::enable_shared_from_this<Point> {
public:
    // 使用 std::enable_shared_from_this 允许对象获取自身的 shared_ptr
    std::shared_ptr<Point> getSharedPtr() { // Correctly formatted comment
        return shared_from_this();
    }

private:
    double x, y;

public:
    // Constructor
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {
        std::cout << "Point created: (" << x << ", " << y << ")" << std::endl;
    }

    // Destructor
    ~Point() {
        std::cout << "Point destroyed: (" << x << ", " << y << ")" << std::endl;
    }

    // Getter for x
    double getX() const {
        return x;
    }

    // Getter for y
    double getY() const {
        return y;
    }

};

class A;
class B;

class A {
private:
    std::shared_ptr<B> b_ptr;

public:
    A() {
        std::cout << "A created" << std::endl;
    }

    ~A() {
        std::cout << "A destroyed" << std::endl;
    }

    void setB(const std::shared_ptr<B>& b) {
        b_ptr = b;
    }
};

class B {
private:
    std::shared_ptr<A> a_ptr;

public:
    B() {
        std::cout << "B created" << std::endl;
    }

    ~B() {
        std::cout << "B destroyed" << std::endl;
    }

    void setA(const std::shared_ptr<A>& a) {
        a_ptr = a;
    }
};

int main() {
    // Point* point_ptr = new Point(1.0, 2.0); // 创建一个 Point 对象
    // std::shared_ptr<Point> p1(point_ptr); // 使用 shared_ptr 管理 Point 对象
    // std::cout << "p1 use count: " << p1.use_count() << std::endl; // 输出引用计数
    // std::shared_ptr<Point> p2 = p1;

    // std::cout << "p1 use count: " << p1.use_count() << std::endl;
    // std::cout << "p2 use count: " << p2.use_count() << std::endl;

    // std::shared_ptr<Point> p1(new Point(1.0, 2.0)); // 创建一个 Point 对象并用 shared_ptr 管理
    // std::cout << "p1 use count: " << p1.use_count() << std::endl; // 输出引用计数
    // std::shared_ptr<Point> p2 = p1->getSharedPtr(); // 使用 enable_shared_from_this 获取 shared_ptr
    // std::cout << "p1 use count: " << p1.use_count() << std::endl; // 输出引用计数
    // std::cout << "p2 use count: " << p2.use_count() << std::endl; // 输出引用计数   

    A a;
    B b;
    std::shared_ptr<A> a_ptr = std::make_shared<A>(a); // 创建一个 shared_ptr 管理 A 对象
    std::shared_ptr<B> b_ptr = std::make_shared<B>(b); // 创建一个 shared_ptr 管理 B 对象
    a_ptr->setB(b_ptr); // 设置 A 对象的 B 指针
    b_ptr->setA(a_ptr); // 设置 B 对象的 A 指针
    cout << "a_ptr use count: " << a_ptr.use_count() << std::endl; // 输出引用计数
    cout << "b_ptr use count: " << b_ptr.use_count() << std::endl; // 输出引用计数


    return 0;
}