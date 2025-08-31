/* --- Point.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 8/29/2025
------------------------------------------ */

#ifndef POINT_H
#define POINT_H

class Point {
 public:
  /**
   * @brief Constructor for Point.
   * @param x X coordinate (default 0).
   * @param y Y coordinate (default 0).
   */
  Point(double x = 0, double y = 0);

  /**
   * @brief Destructor for Point.
   */
  ~Point();

  /**
   * @brief Get the X coordinate.
   * @return X coordinate value.
   */
  double GetX() const;

  /**
   * @brief Get the Y coordinate.
   * @return Y coordinate value.
   */
  double GetY() const;

 private:
  double x_;
  double y_;
};

#endif  // POINT_H
