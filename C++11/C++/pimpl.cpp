// pimpl.cpp
#include <iostream>
#include <memory>
using namespace std;

// 前向声明实现类
class WidgetImpl;

// 接口类
class Widget {
public:
    Widget(int x);
    ~Widget();

    void show() const;

private:
    unique_ptr<WidgetImpl> impl_; // 指向实现的指针
};

// 实现类定义（只在cpp文件中可见）
class WidgetImpl {
public:
    WidgetImpl(int x) : data(x) {}
    void show() const { cout << "WidgetImpl data: " << data << endl; }
private:
    int data;
};

// Widget成员函数实现
Widget::Widget(int x) : impl_(make_unique<WidgetImpl>(x)) {}
Widget::~Widget() = default;
void Widget::show() const { impl_->show(); }

// 测试
int main() {
    Widget w(42);
    w.show();
    return 0;
}