#include <iostream>
#include <fstream>
// #include <nlohmann/json.hpp>
# include "./include/json.hpp"
using json = nlohmann::json;
using namespace std;

int main() {
    ifstream fin("d:/work_directory/git_work/program_coding/program/woven0828/PolygonOverlap/hulls.json");
    if (!fin) {
        cerr << "Cannot open file!" << endl;
        return 1;
    }
    json j;
    fin >> j;

    // 遍历 convex hulls
    for (const auto& hull : j["convex hulls"]) {
        cout << "ID: " << hull["ID"] << endl;
        for (const auto& apex : hull["apexes"]) {
            cout << "  x: " << apex["x"] << ", y: " << apex["y"] << endl;
        }
    }
    return 0;
}