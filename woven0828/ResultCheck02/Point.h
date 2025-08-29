/* --- Point.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 8/29/2025
------------------------------------------ */

#ifndef POINT_H
#define POINT_H

class Point2D {
public:
    Point2D(double x =0.0, double y =0.0)
        : x_(x)
        , y_(y)
    {

    }
    ~Point2D();

    double getX() const
    {
        return x_;
    }

    double getY() const
    {
        return y_;
    }

private:
    double x_;
    double y_;
};

#endif // POINT_H
