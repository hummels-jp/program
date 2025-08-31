#include "point_in_polygon.h"
#include <iostream>
#include <vector>

/**
 * @brief Determines if a point is inside a polygon using the ray casting algorithm.
 * @param pt The point to test.
 * @param polygon The polygon represented as a vector of points.
 * @return true if the point is inside the polygon, false otherwise.
 */
bool PointInPolygon(const Point& pt, const std::vector<Point>& polygon) {
    int n = polygon.size();
    int count = 0;
    for (int i = 0; i < n; ++i) {
        const Point& a = polygon[i];
        const Point& b = polygon[(i + 1) % n];
        if ((a.y > pt.y) != (b.y > pt.y)) {
            double intersect_x = (b.x - a.x) * (pt.y - a.y) / (b.y - a.y + 1e-20) + a.x;
            if (pt.x < intersect_x)
                count++;
        }
    }
    return count % 2 == 1;
}

int main() {
    // Example polygon (either clockwise or counterclockwise)
    std::vector<Point> polygon = {
        {0.0, 0.0},
        {10.0, 0.0},
        {10.0, 10.0},
        {0.0, 10.0}
    };

    Point pt = {-29.317074184905096, 14.70919261723742};

    if (PointInPolygon(pt, polygon)) {
        std::cout << "Point is inside the polygon." << std::endl;
    } else {
        std::cout << "Point is outside the polygon." << std::endl;
    }

    return 0;
}
