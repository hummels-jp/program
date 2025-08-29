
#include <iostream>
#include <string>
#include "PolygonFilter.h"

int main() {
    try {
        PolygonFilter filter;
        std::string input_json = "../hulls.json";
        std::string output_json = "../output.json";
        filter.read_from_json(input_json);
        filter.loop_polygons();
        filter.output_json(output_json);
        std::cout << "过滤和输出完成，结果已写入 output.json" << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "发生异常: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}