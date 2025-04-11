#include <iostream>
#include <vector>
#include <algorithm>

class Point {
public:
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // 可选：打印函数
    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

// 比较器类：重载 ()，可用于排序
// 仿函数需要些一个对应的仿函数类
class PointComparator {
public:
    // 比如按 x 从小到大排序，若 x 相同则按 y
    bool operator()(const Point& a, const Point& b) const {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }
};

int main() {
    std::vector<Point> points = { {3, 4}, {1, 2}, {3, 1}, {2, 5} };

    std::sort(points.begin(), points.end(), PointComparator());

    for (const auto& p : points) {
        p.print();
        std::cout << " ";
    }

    return 0;
}
