/* --- PolygonFilter.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 8/29/2025
------------------------------------------ */
#include "pch.h"
#include "PolygonFilter.h"


PolygonFilter::PolygonFilter() {
    // Constructor
}

std::vector<Polygon2D>& PolygonFilter::read_from_json(std::string fileName)
{
    std::ifstream fin(fileName);
    if (!fin) {
        throw std::runtime_error("Cannot open hulls.json");
    }
    json j;
    fin >> j;
    polygons_.clear();
    for (const auto& hull : j["convex hulls"]) {
        Polygon2D poly;
        // 读取ID
        if (hull.contains("ID")) {
            poly.set_polygon_id(hull["ID"]);
        }
        for (const auto& apex : hull["apexes"]) {
            Point2D pt(apex["x"], apex["y"]);
            poly.get_points().push_back(pt);
        }
        polygons_.push_back(poly);
    }


    // 输出 polygons_ 的个数
    std::string msg = "Successfully read polygons from JSON file.\nCount: " + std::to_string(polygons_.size());
    MessageBoxA(NULL, msg.c_str(), "Info", MB_OK | MB_ICONINFORMATION);
    return polygons_;
}


PolygonFilter::~PolygonFilter() {
    // Destructor
}