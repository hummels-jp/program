/* --- Polygon.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 8/29/2025
------------------------------------------ */

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <math.h>
#include <algorithm>
#include "Point.h"

class Polygon2D {
public:
    Polygon2D();
    Polygon2D(std::vector<Point2D> points);
    ~Polygon2D();

public:

    std::vector<Point2D>& get_points()
    {
        return points_;
    }

    void set_polygon_id(int polgyon_id)
    {
        polygon_id_ = polgyon_id;
    }

    int get_polygon_id() const
    {
        return polygon_id_;
    }


public:
    std::vector<Point2D> points_; // store the points of polygon
    int polygon_id_; // polygon id
};

#endif // POLYGON_H
