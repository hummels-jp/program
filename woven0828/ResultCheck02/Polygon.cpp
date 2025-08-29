/* --- Polygon.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 8/29/2025
------------------------------------------ */
#include "pch.h"
#include "Polygon.h"


Polygon2D::Polygon2D()
{
}

Polygon2D::Polygon2D(std::vector<Point2D> points)
    : points_(points)

{

}

Polygon2D::~Polygon2D()
{
    // Destructor
}
