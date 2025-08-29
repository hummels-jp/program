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
        // Read ID
        if (hull.contains("ID")) {
            poly.set_polygon_id(hull["ID"]);
        }
        for (const auto& apex : hull["apexes"]) {
            Point pt(apex["x"], apex["y"]);
            poly.get_points().push_back(pt);
        }

        poly.set_max_ratio(0.0);
        polygons_.push_back(poly);
    }

    // Print each Polygon's attributes
    // for (auto& poly : polygons_) {
    //     std::cout << "Polygon ID: " << poly.get_polygon_id()
    //               << ", Area: " << poly.get_area()
    //               << ", Max Ratio: " << poly.get_max_ratio()
    //               << std::endl;
    //     // std::cout << "Apexes: ";
    //     // for (const auto& pt : poly.get_points()) {
    //     //     std::cout << "(" << pt.getX() << ", " << pt.getY() << ") ";
    //     // }
    //     // std::cout << std::endl;
    // }
}

void PolygonFilter::loop_polygons()
{
    int n = polygons_.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            polygons_[i].polygon_overlap(polygons_[j]);
            // polygon_overlap will automatically update max_ratio_
        }
    }

    // Print each Polygon's attributes
    // std::cout << "after loop " << std::endl;
    // for (auto& poly : polygons_) {
    //     std::cout << "Polygon ID: " << poly.get_polygon_id()
    //               << ", Area: " << poly.get_area()
    //               << ", Max Ratio: " << poly.get_max_ratio()
    //               << std::endl;
    // }
}

void PolygonFilter::output_json(std::string file_name)
{
    json j;
    j["convex hulls"] = json::array();
    for (auto& poly : polygons_) {
        if (poly.get_max_ratio() >= 0.5) { // Only output polygons with max_ratio_ >= 0.5
            json hull;
            hull["ID"] = poly.get_polygon_id(); // Polygon ID
            hull["max_ratio"] = poly.get_max_ratio(); // Optional: output max_ratio
            hull["apexes"] = json::array();
            for (auto& pt : poly.get_points()) {
                hull["apexes"].push_back({ {"x", pt.getX()}, {"y", pt.getY()} });
            }
            j["convex hulls"].push_back(hull);
        }
    }
    std::ofstream fout(file_name);
    if (!fout) {
        throw std::runtime_error("Cannot open output.json for writing");
    }
    fout << j.dump(4); // Pretty print
    fout.close();

    std::cout << "output finished " << std::endl;
}

// polygons_ is the member variable storing all polygons
int PolygonFilter::get_polygon_count() const {
    return static_cast<int>(polygons_.size());
}

// Process overlap calculation between current Polygon and those after idx
void PolygonFilter::process_polygon(int idx) {
    int n = polygons_.size();
    for (int j = idx + 1; j < n; ++j) {
        polygons_[idx].polygon_overlap(polygons_[j]);
        // polygon_overlap will automatically update max_ratio_
    }
}

PolygonFilter::~PolygonFilter() {
    // Destructor
}