/* --- Polygon.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 8/29/2025
------------------------------------------ */

#include "Polygon.h"
#include <cmath>

/**
 * @brief Default constructor for Polygon.
 */
Polygon::Polygon() : max_ratio_(0.0), polygon_id_(0) {}

/**
 * @brief Constructor for Polygon with a vector of points.
 * @param points Vector of Point objects representing the polygon vertices.
 */
Polygon::Polygon(std::vector<Point> points)
    : points_(std::move(points)), max_ratio_(0.0), polygon_id_(0) {}

/**
 * @brief Destructor for Polygon.
 */
Polygon::~Polygon() {}

/**
 * @brief Calculates the area of the polygon.
 * @return Area of the polygon.
 */
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

/**
 * @brief Checks if two polygons overlap. If overlapped, updates max_ratio_.
 * @param polygon The other polygon to check overlap with.
 * @return True if the polygons overlap, false otherwise.
 */
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
            // If both P and Q are inside the current clipping edge (A,B), keep Q in the intersection polygon.
            if (Pin && Qin) {
                intersection.push_back(Q);
            } else if (Pin && !Qin) {
                // P is inside and Q is outside: add intersection point between edge and clip boundary.
                double dx = Q.GetX() - P.GetX();
                double dy = Q.GetY() - P.GetY();
                double da = cross(A, B, P);
                double db = cross(A, B, Q);
                double t = da / (da - db);
                Point inter(P.GetX() + t * dx, P.GetY() + t * dy);
                intersection.push_back(inter);
            } else if (!Pin && Qin) {
                // P is outside and Q is inside: add intersection point and Q.
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

    // Calculate the area of the intersection polygon using the shoelace formula.
    double overlap_area = 0.0;
    if (intersection.size() >= 3) {
        for (size_t i = 0; i < intersection.size(); ++i) {
            const Point& p1 = intersection[i];
            const Point& p2 = intersection[(i + 1) % intersection.size()];
            // Accumulate the cross product for each edge.
            overlap_area += (p1.GetX() * p2.GetY()) - (p2.GetX() * p1.GetY());
        }
        // Take the absolute value and divide by 2 to get the polygon area.
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

/**
 * @brief Get the vector of points of the polygon.
 * @return Reference to the vector of points.
 */
std::vector<Point>& Polygon::Points()
{
    return points_;
}

/**
 * @brief Set the maximum area ratio for overlap.
 * @param max_ratio The maximum ratio value.
 */
void Polygon::SetMaxRatio(double max_ratio)
{
    max_ratio_ = max_ratio;
}

/**
 * @brief Get the maximum area ratio for overlap.
 * @return The maximum ratio value.
 */
double Polygon::MaxRatio() const
{
    return max_ratio_;
}

/**
 * @brief Set the polygon ID.
 * @param polygon_id The polygon ID.
 */
void Polygon::SetPolygonId(int polygon_id)
{
    polygon_id_ = polygon_id;
}

/**
 * @brief Get the polygon ID.
 * @return The polygon ID.
 */
int Polygon::PolygonId() const
{
    return polygon_id_;
}
