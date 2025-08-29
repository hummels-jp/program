#include <iostream>
#include <string>
#include "PolygonFilter.h"

int main() {
    try {
        PolygonFilter filter;
        // std::string input_json = "../input/test1.json";
        std::string input_json = "../input/convex_hulls.json";
        std::string output_json = "../output/output.json";
        filter.read_from_json(input_json);
        filter.loop_polygons();
        filter.output_json(output_json);
        std::cout << "Filtering and output completed. Results have been written to output.json." << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}