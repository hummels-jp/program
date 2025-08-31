#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <thread>

#include "PolygonFilter.h"
#include "ThreadPool.h"

int main(int argc, char* argv[]) {
    // 参数说明:
    // argv[1]: input_json
    // argv[2]: output_json
    // argv[3]: mode ("single" or "multi")
    // argv[4]: min_threads (only for multi)

    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <input_json> <output_json> <single|multi> [min_threads]" << std::endl;
        return 1;
    }
    std::string input_json = argv[1];
    std::string output_json = argv[2];
    std::string mode = argv[3];
    int min_threads = 2;
    int max_threads = std::thread::hardware_concurrency();
    if (mode == "multi" && argc >= 5) {
        min_threads = std::atoi(argv[4]);
        if (min_threads <= 0) min_threads = 2;
    }

    try {
        auto start = std::chrono::high_resolution_clock::now();
        PolygonFilter filter;
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

        if (mode == "single") {
            filter.loop_polygons();
        } else if (mode == "multi") {
            ThreadPool pool(min_threads, max_threads);
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
        } else {
            std::cerr << "Unknown mode: " << mode << ". Use 'single' or 'multi'." << std::endl;
            return 1;
        }

        filter.output_json(output_json);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Filtering and output completed. Results have been written to " << output_json << std::endl;
        std::cout << "Execution time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}