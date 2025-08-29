/* --- Polygon.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 8/29/2025
------------------------------------------ */

#include "Polygon.h"

Polygon::Polygon()
    : max_ratio_(0.0)
{
}

Polygon::Polygon(std::vector<Point> points)
    : points_(points)
    , max_ratio_(0.0)
{
}

bool Polygon::segments_intersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2)
{
    auto cross = [](const Point& a, const Point& b, const Point& c) {
        // 计算向量 ab 和 ac 的叉积
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    };

    auto d1 = cross(q1, q2, p1);
    auto d2 = cross(q1, q2, p2);
    auto d3 = cross(p1, p2, q1);
    auto d4 = cross(p1, p2, q2);
    if (((d1>0 && d2<0) || (d1<0 && d2>0)) && ((d3>0 && d4<0) || (d3<0 && d4>0)))
        return true;
    return false;
}

bool Polygon::point_inside_polygon(const Point& point)
{
    int n = points_.size();
    int cnt = 0;
    double x = point.getX(), y = point.getY();
    for (int i = 0; i < n; ++i) {
        const Point& a = points_[i];
        const Point& b = points_[(i + 1) % n];
        double x1 = a.getX(), y1 = a.getY();
        double x2 = b.getX(), y2 = b.getY();

        // 判断射线是否与边相交
        if ((y1 > y) != (y2 > y)) {
            if (y2 - y1 != 0) { // 防止除零
                double intersectX = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                if (intersectX > x)
                    cnt++;
            }
        }
    }
    return cnt % 2 == 1;
}

bool Polygon::polygon_overlap(Polygon& polygon)
{
    // 1. 计算重叠区域（Sutherland–Hodgman 多边形裁剪算法）
    std::vector<Point> intersection = points_;
    int n = polygon.get_points().size();
    for (int i = 0; i < n; ++i) {
        std::vector<Point> input = intersection;
        intersection.clear();
        if (input.empty()) break;
        const Point& A = polygon.get_points()[i];
        const Point& B = polygon.get_points()[(i + 1) % n];
        for (size_t j = 0; j < input.size(); ++j) {
            const Point& P = input[j];
            const Point& Q = input[(j + 1) % input.size()];
            // 判断点在裁剪边的内外
            auto cross = [](const Point& a, const Point& b, const Point& c) {
                return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
            };
            bool Pin = cross(A, B, P) >= 0;
            bool Qin = cross(A, B, Q) >= 0;
            if (Pin && Qin) {
                intersection.push_back(Q);
            } else if (Pin && !Qin) {
                // P在内Q在外，加入交点
                double dx = Q.getX() - P.getX();
                double dy = Q.getY() - P.getY();
                double da = cross(A, B, P);
                double db = cross(A, B, Q);
                double t = da / (da - db);
                Point inter(P.getX() + t * dx, P.getY() + t * dy);
                intersection.push_back(inter);
            } else if (!Pin && Qin) {
                // P在外Q在内，加入交点和Q
                double dx = Q.getX() - P.getX();
                double dy = Q.getY() - P.getY();
                double da = cross(A, B, P);
                double db = cross(A, B, Q);
                double t = da / (da - db);
                Point inter(P.getX() + t * dx, P.getY() + t * dy);
                intersection.push_back(inter);
                intersection.push_back(Q);
            }
        }
    }

    // 2. 计算重叠区域面积
    double overlap_area = 0.0;
    if (intersection.size() >= 3) {
        for (size_t i = 0; i < intersection.size(); ++i) {
            const Point& p1 = intersection[i];
            const Point& p2 = intersection[(i + 1) % intersection.size()];
            overlap_area += (p1.getX() * p2.getY()) - (p2.getX() * p1.getY());
        }
        overlap_area = std::abs(overlap_area) * 0.5;
    }

    // 3. 计算比例并更新 max_ratio_
    double area1 = this->get_area();
    double area2 = polygon.get_area();
    double ratio = (area1 > 0) ? (overlap_area / area1) : 0.0;
    if (ratio > max_ratio_) max_ratio_ = ratio;

    double other_ratio = (area2 > 0) ? (overlap_area / area2) : 0.0;
    if (other_ratio > polygon.max_ratio_) polygon.set_max_ratio(other_ratio);

    // 4. 返回是否有重叠
    return overlap_area > 0.0;
}

Polygon::~Polygon()
{
    // Destructor
}
