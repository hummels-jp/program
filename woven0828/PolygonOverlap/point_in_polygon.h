#pragma once

#include <vector>

/**
 * @brief 2D point structure.
 */
struct Point {
    double x;
    double y;
};

/**
 * @brief Determines if a point is inside a polygon using the ray casting algorithm.
 * @param pt The point to test.
 * @param polygon The polygon represented as a vector of points.
 * @return true if the point is inside the polygon, false otherwise.
 */
bool PointInPolygon(const Point& pt, const std::vector<Point>& polygon);
