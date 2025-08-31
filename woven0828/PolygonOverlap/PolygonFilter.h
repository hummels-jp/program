/* --- PolygonFilter.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 8/29/2025
------------------------------------------ */

#ifndef POLYGONFILTER_H
#define POLYGONFILTER_H
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "Point.h"
#include "Polygon.h"
#include "./include/json.hpp"

using json = nlohmann::json;

class PolygonFilter {
 public:
  /**
   * @brief Default constructor for PolygonFilter.
   */
  PolygonFilter();

  /**
   * @brief Destructor for PolygonFilter.
   */
  ~PolygonFilter();

  /**
   * @brief Reads data from a JSON file and constructs the polygon set.
   * @param file_name The path to the JSON file.
   */
  void ReadFromJson(const std::string& file_name);

  /**
   * @brief Loops through the polygon set and updates each polygon's max_ratio_ value.
   */
  void LoopPolygons();

  /**
   * @brief Filters and outputs the remaining polygons to a JSON file.
   * @param file_name The output JSON file path.
   */
  void OutputJson(const std::string& file_name);

  /**
   * @brief Gets the number of polygons in the set.
   * @return The number of polygons.
   */
  int GetPolygonCount() const;

  /**
   * @brief Processes overlap calculation between the current polygon and all subsequent polygons.
   * @param idx The index of the current polygon.
   */
  void ProcessPolygon(int idx);

 private:
  std::vector<Polygon> polygons_;  // Stores the polygons.
};

#endif  // POLYGONFILTER_H
