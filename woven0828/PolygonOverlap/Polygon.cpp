/* --- Polygon.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 8/29/2025
------------------------------------------ */

#include "Polygon.h"
#include <cmath>

Polygon::Polygon() : max_ratio_(0.0), polygon_id_(0) {}

Polygon::Polygon(std::vector<Point> points)
    : points_(std::move(points)), max_ratio_(0.0), polygon_id_(0) {}

Polygon::~Polygon() {}

double Polygon::GetArea() const
{
    if (points_.size() < 3) return 0.0;
    double area = 0.0;
    int n = points_.size();
    for (int i = 0; i < n; ++i) {
        const Point& p1 = points_[i];
        const Point& p2 = points_[(i + 1) % n];
        area += (p1.GetX() * p2.GetY()) - (p2.GetX() * p1.GetY());
    }
    return std::abs(area) * 0.5;
}

bool Polygon::SegmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2)
{
    auto cross = [](const Point& a, const Point& b, const Point& c) {
        return (b.GetX() - a.GetX()) * (c.GetY() - a.GetY()) - (b.GetY() - a.GetY()) * (c.GetX() - a.GetX());
    };

    auto d1 = cross(q1, q2, p1);
    auto d2 = cross(q1, q2, p2);
    auto d3 = cross(p1, p2, q1);
    auto d4 = cross(p1, p2, q2);
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;
    return false;
}

bool Polygon::PointInsidePolygon(const Point& point)
{
    int n = points_.size();
    int cnt = 0;
    double x = point.GetX(), y = point.GetY();
    for (int i = 0; i < n; ++i) {
        const Point& a = points_[i];
        const Point& b = points_[(i + 1) % n];
        double x1 = a.GetX(), y1 = a.GetY();
        double x2 = b.GetX(), y2 = b.GetY();

        if ((y1 > y) != (y2 > y)) {
            if (y2 - y1 != 0) {
                double intersectX = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                if (intersectX > x)
                    cnt++;
            }
        }
    }
    return cnt % 2 == 1;
}

bool Polygon::PolygonOverlap(Polygon& polygon)
{
    std::vector<Point> intersection = points_;
    int n = polygon.Points().size();
    for (int i = 0; i < n; ++i) {
        std::vector<Point> input = intersection;
        intersection.clear();
        if (input.empty()) break;
        const Point& A = polygon.Points()[i];
        const Point& B = polygon.Points()[(i + 1) % n];
        for (size_t j = 0; j < input.size(); ++j) {
            const Point& P = input[j];
            const Point& Q = input[(j + 1) % input.size()];
            auto cross = [](const Point& a, const Point& b, const Point& c) {
                return (b.GetX() - a.GetX()) * (c.GetY() - a.GetY()) - (b.GetY() - a.GetY()) * (c.GetX() - a.GetX());
            };
            bool Pin = cross(A, B, P) >= 0;
            bool Qin = cross(A, B, Q) >= 0;
            if (Pin && Qin) {
                intersection.push_back(Q);
            } else if (Pin && !Qin) {
                double dx = Q.GetX() - P.GetX();
                double dy = Q.GetY() - P.GetY();
                double da = cross(A, B, P);
                double db = cross(A, B, Q);
                double t = da / (da - db);
                Point inter(P.GetX() + t * dx, P.GetY() + t * dy);
                intersection.push_back(inter);
            } else if (!Pin && Qin) {
                double dx = Q.GetX() - P.GetX();
                double dy = Q.GetY() - P.GetY();
                double da = cross(A, B, P);
                double db = cross(A, B, Q);
                double t = da / (da - db);
                Point inter(P.GetX() + t * dx, P.GetY() + t * dy);
                intersection.push_back(inter);
                intersection.push_back(Q);
            }
        }
    }

    double overlap_area = 0.0;
    if (intersection.size() >= 3) {
        for (size_t i = 0; i < intersection.size(); ++i) {
            const Point& p1 = intersection[i];
            const Point& p2 = intersection[(i + 1) % intersection.size()];
            overlap_area += (p1.GetX() * p2.GetY()) - (p2.GetX() * p1.GetY());
        }
        overlap_area = std::abs(overlap_area) * 0.5;
    }

    double area1 = this->GetArea();
    double area2 = polygon.GetArea();
    double ratio = (area1 > 0) ? (overlap_area / area1) : 0.0;
    if (ratio > max_ratio_) max_ratio_ = ratio;

    double other_ratio = (area2 > 0) ? (overlap_area / area2) : 0.0;
    if (other_ratio > polygon.MaxRatio()) polygon.SetMaxRatio(other_ratio);

    return overlap_area > 0.0;
}

std::vector<Point>& Polygon::Points()
{
    return points_;
}

void Polygon::SetMaxRatio(double max_ratio)
{
    max_ratio_ = max_ratio;
}

double Polygon::MaxRatio() const
{
    return max_ratio_;
}

void Polygon::SetPolygonId(int polygon_id)
{
    polygon_id_ = polygon_id;
}

int Polygon::PolygonId() const
{
    return polygon_id_;
}
