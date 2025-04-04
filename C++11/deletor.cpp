#include <iostream>
#include <memory>

// 自定义删除器函数
void customDeleter(int* ptr) {
    std::cout << "Custom deleter called for pointer: " << ptr << std::endl;
    delete ptr;
}



class Point {
public:
    double m_x, m_y, m_z;

    // Constructor
    Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {
        // std::cout << "Point created: (" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
    }

    // Destructor
    ~Point() {
        std::cout << "Point destroyed: (" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
    }
};


// 自定义删除器函数用于 Point 对象
void pointDeleter(Point* p) {
    std::cout << "Custom deleter for Point called." << std::endl;
    delete p;
}

// 自定义删除器函数用于 Point 数组
struct PointArrayDeleter {
    void operator()(Point* p) const {
        std::cout << "Custom deleter for Point array called." << std::endl;
        delete[] p;
    }
};

int main() {
    // 使用自定义删除器创建 shared_ptr
    // std::shared_ptr<int> sptr(new int(42), customDeleter);
    // std::cout << "Shared pointer value: " << *sptr << std::endl;

    // 创建一个 Point 对象并使用 shared_ptr 管理它
    // std::shared_ptr<Point> pointPtr(new Point(1.0, 2.0, 3.0), pointDeleter);
    // std::cout << "Point is being managed by shared_ptr." << std::endl;


    // // 使用默认删除器创建 shared_ptr 管理 Point 对象
    // std::shared_ptr<Point> defaultDeleterPointPtr = std::make_shared<Point>(4.0, 5.0, 6.0);
    // std::cout << "Default deleter is managing a Point object." << std::endl;



    // 使用自定义删除器管理 10 个 Point 对象
    // std::shared_ptr<Point[]> pointsArray(new Point[10]{
    //     {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0},
    //     {10.0, 11.0, 12.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0},
    //     {19.0, 20.0, 21.0}, {22.0, 23.0, 24.0}, {25.0, 26.0, 27.0},
    //     {28.0, 29.0, 30.0}
    // }, PointArrayDeleter());
    // std::cout << "Shared pointer is managing an array of 10 Points." << std::endl;

    // 使用默认删除器管理 10 个 Point 对象的 shared_ptr
    std::shared_ptr<Point[]> defaultDeleterPointsArray(new Point[10]{
        {31.0, 32.0, 33.0}, {34.0, 35.0, 36.0}, {37.0, 38.0, 39.0},
        {40.0, 41.0, 42.0}, {43.0, 44.0, 45.0}, {46.0, 47.0, 48.0},
        {49.0, 50.0, 51.0}, {52.0, 53.0, 54.0}, {55.0, 56.0, 57.0},
        {58.0, 59.0, 60.0}
    });
    std::cout << "Default deleter is managing an array of 10 Points." << std::endl;

   

    return 0;
}