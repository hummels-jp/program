/* --- Polygon.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 8/29/2025
------------------------------------------ */

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <math.h>
#include "Point.h"
class Polygon {
public:
    Polygon();

    Polygon(std::vector<Point> points);
    ~Polygon();

public:
    // calculate the polygon area
    double get_area() const
    {
        if (points_.size() < 3) return 0.0;
        double area = 0.0;
        int n = points_.size();
        for (int i = 0; i < n; ++i) {
            const Point& p1 = points_[i];
            const Point& p2 = points_[(i + 1) % n];
            area += (p1.getX() * p2.getY()) - (p2.getX() * p1.getY());
        }
        return std::abs(area) * 0.5;
    }

    // whether two sement are crossed
    bool segments_intersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2);

public:
    // whether the point is inside the polygon
    bool point_inside_polygon(const Point& point);

    // whether the two polygon is overlapped
    // if overlapped, update the polygon max_ration member
    bool polygon_overlap(Polygon& polygon);

    std::vector<Point>& get_points()
    {
        return points_;
    }

    void set_max_ratio(double max_ratio)
    {
        max_ratio_ = max_ratio;
    }

    double get_max_ratio() const
    {
        return max_ratio_;
    }

    void set_polygon_id(int polgyon_id)
    {
        polygon_id_ = polgyon_id;
    }

    int get_polygon_id() const
    {
        return polygon_id_;
    }


private:
    std::vector<Point> points_; // store the points of polygon
    double max_ratio_; // if this polygon overlap with other polygons, store the max area ratio
    int polygon_id_; // polygon id
};

#endif // POLYGON_H
