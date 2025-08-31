// This file follows the Google C++ Style Guide: https://google.github.io/styleguide/cppguide.html
/* --- Polygon.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 8/29/2025
------------------------------------------ */

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <cmath>
#include "Point.h"

class Polygon {
 public:
  /**
   * @brief Default constructor for Polygon.
   */
  Polygon();

  /**
   * @brief Constructor for Polygon with a vector of points.
   * @param points Vector of Point objects representing the polygon vertices.
   */
  explicit Polygon(std::vector<Point> points);

  /**
   * @brief Destructor for Polygon.
   */
  ~Polygon();

  /**
   * @brief Calculates the area of the polygon.
   * @return Area of the polygon.
   */
  double GetArea() const;

  /**
   * @brief Checks if two segments intersect.
   * @param p1 First endpoint of the first segment.
   * @param p2 Second endpoint of the first segment.
   * @param q1 First endpoint of the second segment.
   * @param q2 Second endpoint of the second segment.
   * @return True if the segments intersect, false otherwise.
   */
  bool SegmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2);

  /**
   * @brief Checks if a point is inside the polygon.
   * @param point The point to check.
   * @return True if the point is inside, false otherwise.
   */
  bool PointInsidePolygon(const Point& point);

  /**
   * @brief Checks if two polygons overlap. If overlapped, updates max_ratio_.
   * @param polygon The other polygon to check overlap with.
   * @return True if the polygons overlap, false otherwise.
   */
  bool PolygonOverlap(Polygon& polygon);

  /**
   * @brief Get the vector of points of the polygon.
   * @return Reference to the vector of points.
   */
  std::vector<Point>& Points();

  /**
   * @brief Set the maximum area ratio for overlap.
   * @param max_ratio The maximum ratio value.
   */
  void SetMaxRatio(double max_ratio);

  /**
   * @brief Get the maximum area ratio for overlap.
   * @return The maximum ratio value.
   */
  double MaxRatio() const;

  /**
   * @brief Set the polygon ID.
   * @param polygon_id The polygon ID.
   */
  void SetPolygonId(int polygon_id);

  /**
   * @brief Get the polygon ID.
   * @return The polygon ID.
   */
  int PolygonId() const;

 private:
  std::vector<Point> points_;  // Stores the points of the polygon.
  double max_ratio_;           // Stores the max area ratio if this polygon overlaps with others.
  int polygon_id_;             // Polygon id.
};

#endif  // POLYGON_H
