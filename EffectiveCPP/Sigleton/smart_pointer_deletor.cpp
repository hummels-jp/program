#include <iostream>
#include <memory>
using namespace std;

class Point {
public:
    Point(int x, int y) : _x(x), _y(y) {
        cout << "Point(" << _x << ", " << _y << ") 构造" << endl;
    }
    void show() const {
        cout << "Point: (" << _x << ", " << _y << ")" << endl;
    }
private:
    int _x, _y;
    ~Point() { // 析构函数私有
        cout << "Point(" << _x << ", " << _y << ") 析构" << endl;
    }
    // 友元声明允许删除器访问析构
    friend struct PointDeletor;
};

// 自定义删除器，作为友元
struct PointDeletor {
    void operator()(Point* p) const {
        cout << "customized deletor " << endl;
        delete p; // 可以访问私有析构
    }
};

int main() {
    unique_ptr<Point, PointDeletor> uptr(new Point(1, 2));
    // deconstruct object, call the pointDeletor
    uptr->show();

    // shared_ptr 也可以
    shared_ptr<Point> sptr(new Point(3, 4), PointDeletor());
    sptr->show();

    // delete uptr.get(); // 编译错误，析构函数私有
    // delete sptr.get(); // 编译错误，析构函数私有

    return 0;
}