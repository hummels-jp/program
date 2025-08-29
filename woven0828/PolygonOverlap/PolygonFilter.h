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
    PolygonFilter();
    ~PolygonFilter();

    // read data from json, construct polygon set
    void read_from_json(std::string file_name);

    // loop the polygon set, update the polygon max_ratio_ value
    void loop_polygons();

    // filter and output the rest polygons.
    void output_json(std::string file_name);

private:
    std::vector<Polygon> polygons_; // store the polygons;

};

#endif // POLYGONFILTER_H
