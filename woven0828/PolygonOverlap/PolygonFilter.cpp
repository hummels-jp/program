/* --- PolygonFilter.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 8/29/2025
------------------------------------------ */

#include "PolygonFilter.h"

PolygonFilter::PolygonFilter() {
    // Constructor
}

void PolygonFilter::read_from_json(std::string fileName)
{
    std::ifstream fin(fileName);
    if (!fin) {
        throw std::runtime_error("Cannot open hulls.json");
    }
    json j;
    fin >> j;
    polygons_.clear();
    for (const auto& hull : j["convex hulls"]) {
        Polygon poly;
        // 读取ID
        if (hull.contains("ID")) {
            poly.set_polygon_id(hull["ID"]);
        }
        for (const auto& apex : hull["apexes"]) {
            Point pt(apex["x"], apex["y"]);
            poly.get_points().push_back(pt);
        }
        poly.set_area(poly.get_area());
        poly.set_max_ratio(0.0);
        polygons_.push_back(poly);
    }

    // 输出每个Polygon的属性值
    for (const auto& poly : polygons_) {
        std::cout << "Polygon ID: " << poly.get_polygon_id()
                  << ", Area: " << poly.get_area()
                  << ", Max Ratio: " << poly.get_max_ratio()
                  << std::endl;
    }

    
}

void PolygonFilter::loop_polygons()
{
    int n = polygons_.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            polygons_[i].polygon_overlap(polygons_[j]);
            // polygon_overlap 内部会自动更新 max_ratio_
        }
    }

    // 输出每个Polygon的属性值
    for (const auto& poly : polygons_) {
        std::cout << "Polygon ID: " << poly.get_polygon_id()
                  << ", Area: " << poly.get_area()
                  << ", Max Ratio: " << poly.get_max_ratio()
                  << std::endl;
    }
}

void PolygonFilter::output_json(std::string file_name)
{
    json j;
    j["convex hulls"] = json::array();
    for (const auto& poly : polygons_) {
        if (poly.get_max_ratio() <= 0.5) { // 只输出max_ratio_小于等于0.5的
            json hull;
            hull["ID"] = poly.get_polygon_id(); // 获取多边形ID
            hull["max_ratio"] = poly.get_max_ratio(); // 可选：输出max_ratio
            hull["apexes"] = json::array();
            for (const auto& pt : poly.get_points()) {
                hull["apexes"].push_back({ {"x", pt.getX()}, {"y", pt.getY()} });
            }
            j["convex hulls"].push_back(hull);
        }
    }
    std::ofstream fout(file_name);
    if (!fout) {
        throw std::runtime_error("Cannot open output.json for writing");
    }
    fout << j.dump(4); // 美化输出
    fout.close();
}

PolygonFilter::~PolygonFilter() {
    // Destructor
}
