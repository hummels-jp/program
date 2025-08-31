/* --- Point.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 8/29/2025
------------------------------------------ */

#include "Point.h"

/**
 * @brief Constructor for Point.
 * @param x X coordinate (default 0).
 * @param y Y coordinate (default 0).
 */
Point::Point(double x, double y)
    : x_(x), y_(y)
{
}

/**
 * @brief Destructor for Point.
 */
Point::~Point()
{
}

/**
 * @brief Get the X coordinate.
 * @return X coordinate value.
 */
double Point::GetX() const
{
    return x_;
}

/**
 * @brief Get the Y coordinate.
 * @return Y coordinate value.
 */
double Point::GetY() const
{
    return y_;
}
