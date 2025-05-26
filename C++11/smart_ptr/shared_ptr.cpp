#include <iostream>
#include <memory>

class Point {
private:
    double m_x, m_y, m_z;

public:
    // Default constructor
    Point() : m_x(0), m_y(0), m_z(0) {
        std::cout << "Point default constructed" << std::endl;
    }

    // Parameterized constructor
    Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {
        std::cout << "Point constructed with values (" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
    }

    // Destructor
    ~Point() {
        std::cout << "Point destructed" << std::endl;
    }
};

struct PointArrayDeleter {
    void operator()(Point* ptr) const {
        delete[] ptr;
        std::cout << "Custom deleter called for Point array" << std::endl;
    }
};

int main() {

    // Using shared_ptr with a custom deleter for an array of Point objects
    // std::shared_ptr<Point[]> points(new Point[3]);

    // Using shared_ptr with a custom deleter for a single Point object
    std::shared_ptr<Point[3]> singlePoint(new Point[3], PointArrayDeleter());
    return 0;
}