#include "file_search.h"
#include "search_option.h"
#include "search_result.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    // 使用 SearchOption::parseArguments 解析命令行参数
    SearchOption options = SearchOption::parseArguments(argc, argv);

    // 创建 FileSearch 对象
    FileSearch file_search(options.getDirectoryPath(), options);

    // 存储搜索结果
    std::vector<SearchResult> results;

    try {
        // 执行搜索
        file_search.search_directory(results);

        // 输出所有结果
        for (const auto& result : results) {
            std::cout << "File: " << result.getFilePath();
            if (options.isCountOnly() || options.isListOnly() || options.isListOnlyNonMatching()) {
                std::cout << std::endl;
                continue;
            }
            std::cout << ", Line: " << result.getLineNumber();
            if (options.isHighlightMatch()) {
                std::cout << "  Content: \033[1;31m" << result.getLineContent() << "\033[0m" << std::endl;
            } else {
                std::cout << "  Content: " << result.getLineContent() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}