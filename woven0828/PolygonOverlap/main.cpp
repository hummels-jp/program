#include <iostream>
#include <string>
#include <chrono>

#include "PolygonFilter.h"
#include "ThreadPool.h"

int main() {
    // single thread
    // try {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     PolygonFilter filter;
    //     // std::string input_json = "../input/test1.json";
    //     std::string input_json = "../input/convex_hulls_10000.json";
    //     std::string output_json = "../output/output_10000.json";
    //     filter.read_from_json(input_json);
    //     filter.loop_polygons();
    //     filter.output_json(output_json);
    //     auto end = std::chrono::high_resolution_clock::now();
    //     std::cout << "Filtering and output completed. Results have been written to output.json." << std::endl;
    //     std::cout << "Execution time: "
    //               << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    //               << " ms" << std::endl;
    // } catch (const std::exception& ex) {
    //     std::cerr << "Exception occurred: " << ex.what() << std::endl;
    //     return 1;
    // }


    // multi thread
    try {
        auto start = std::chrono::high_resolution_clock::now();
        PolygonFilter filter;
        std::string input_json = "../input/convex_hulls_10000.json";
        std::string output_json = "../output_multi_thread/output_10000.json";
        filter.read_from_json(input_json);

        // Ensure output directory exists
        {
            size_t pos = output_json.find_last_of("/\\");
            if (pos != std::string::npos) {
#ifdef _WIN32
                std::string dir = output_json.substr(0, pos);
                std::string cmd = "if not exist \"" + dir + "\" mkdir \"" + dir + "\"";
                system(cmd.c_str());
#else
                std::string dir = output_json.substr(0, pos);
                std::string cmd = "mkdir -p \"" + dir + "\"";
                system(cmd.c_str());
#endif
            }
        }

        int n = filter.get_polygon_count();
        ThreadPool pool;
        std::vector<std::future<void>> results;
        for (int i = 0; i < n; ++i) {
            results.emplace_back(pool.enqueue([&filter, i] {
                filter.process_polygon(i);
            }));
        }
        for (auto& fut : results) {
            try {
                fut.get();
            } catch (const std::exception& ex) {
                std::cerr << "Exception in thread pool task: " << ex.what() << std::endl;
            }
        }
        pool.shutdown();

        filter.output_json(output_json);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Filtering and output completed. Results have been written to "<< output_json << std::endl;
        std::cout << "Execution time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}