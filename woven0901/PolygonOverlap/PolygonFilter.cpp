/* --- PolygonFilter.cpp --- */

/* ------------------------------------------
author: Huqianqian
date: 8/29/2025
------------------------------------------ */

#include "PolygonFilter.h"

/**
 * @brief Default constructor for PolygonFilter.
 */
PolygonFilter::PolygonFilter() {
    // Constructor
}

/**
 * @brief Reads polygons from a JSON file and populates the polygons_ vector.
 * @param fileName The path to the JSON file.
 */
void PolygonFilter::ReadFromJson(const std::string& file_name)
{
    std::ifstream fin(file_name);
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
            poly.SetPolygonId(hull["ID"]);
        }
        for (const auto& apex : hull["apexes"]) {
            Point pt(apex["x"], apex["y"]);
            poly.Points().push_back(pt);
        }

        poly.SetMaxRatio(0.0);
        polygons_.push_back(poly);
    }
}

/**
 * @brief Loops through all polygons and computes overlap ratios between each pair.
 */
void PolygonFilter::LoopPolygons()
{
    int n = polygons_.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            polygons_[i].PolygonOverlap(polygons_[j]);
            // PolygonOverlap will automatically update max_ratio_
        }
    }
}

/**
 * @brief Outputs polygons with max_ratio_ >= 0.5 to a JSON file.
 * @param file_name The output JSON file path.
 */
void PolygonFilter::OutputJson(const std::string& file_name)
{
    json j;
    j["convex hulls"] = json::array();
    for (auto& poly : polygons_) {
        if (poly.MaxRatio() >= 0.5) { // Only output polygons with max_ratio_ >= 0.5
            json hull;
            hull["ID"] = poly.PolygonId(); // Polygon ID
            hull["max_ratio"] = poly.MaxRatio(); // Optional: output max_ratio
            hull["apexes"] = json::array();
            for (auto& pt : poly.Points()) {
                hull["apexes"].push_back({ {"x", pt.GetX()}, {"y", pt.GetY()} });
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

/**
 * @brief Gets the number of polygons.
 * @return The number of polygons in the filter.
 */
int PolygonFilter::GetPolygonCount() const {
    return static_cast<int>(polygons_.size());
}

/**
 * @brief Processes overlap calculation between the current polygon and all subsequent polygons.
 * @param idx The index of the current polygon.
 */
void PolygonFilter::ProcessPolygon(int idx) {
    int n = polygons_.size();
    for (int j = idx + 1; j < n; ++j) {
        polygons_[idx].PolygonOverlap(polygons_[j]);
        // PolygonOverlap will automatically update max_ratio_
    }
}

/**
 * @brief Destructor for PolygonFilter.
 */
PolygonFilter::~PolygonFilter() {
    // Destructor
}