#include <iostream>
#include <memory>

class Point {
private:
    double m_x, m_y, m_z;

public:
    // Default constructor
    Point() : m_x(0), m_y(0), m_z(0) {
        std::cout << "Point created: (" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
    }
    // Constructor
    Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {
        std::cout << "Point created: (" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
    }

    // Getter functions
    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }

    // Destructor
    ~Point() {
        std::cout << "Point destroyed: (" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
    }
};

struct PointDeleter {
    void operator()(Point* ptr) const {
        std::cout << "Custom deleter is deleting Point." << std::endl;
        delete ptr;
    }
};

int main() {
    // 使用内存赋值的形式创建 unique_ptr
    // std::unique_ptr<int> uniquePtr(new int(42));

    // std::cout << "Value: " << *uniquePtr << std::endl;

    // // 转移所有权到另一个 unique_ptr
    // std::unique_ptr<int> anotherUniquePtr = std::move(uniquePtr);

    // if (!uniquePtr) {
    //     std::cout << "uniquePtr is now null after ownership transfer." << std::endl;
    // }

    // std::cout << "Value in anotherUniquePtr: " << *anotherUniquePtr << std::endl;

    // 使用 unique_ptr 管理一个 Point 对象
    // std::unique_ptr<Point> pointPtr = std::make_unique<Point>(1.0, 2.0, 3.0);

    // // 使用自定义删除器
    // std::unique_ptr<Point, PointDeleter> customDeleterPtr(new Point(4.0, 5.0, 6.0), PointDeleter());
    // // 访问 Point 对象的成员函数（如果有的话）
    // std::cout << "Point coordinates: (" << pointPtr->getX() << ", " << pointPtr->getY() << ", " << pointPtr->getZ() << ")" << std::endl;

    // 使用 unique_ptr 管理一个 Point 的数组
    std::unique_ptr<Point[]> pointArray = std::make_unique<Point[]>(3);

    // 初始化数组中的每个元素
    // pointArray[0] = Point(1.0, 2.0, 3.0);
    // pointArray[1] = Point(4.0, 5.0, 6.0);
    // pointArray[2] = Point(7.0, 8.0, 9.0);

    // // 访问数组中的元素
    // for (int i = 0; i < 3; ++i) {
    //     std::cout << "Point " << i << ": ("
    //               << pointArray[i].getX() << ", "
    //               << pointArray[i].getY() << ", "
    //               << pointArray[i].getZ() << ")" << std::endl;
    // }
    return 0;
}