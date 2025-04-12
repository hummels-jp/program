#include "file_search.h"
#include "search_option.h"
#include "search_result.h"
#include <iostream>
#include <regex>
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

            // 检查是否启用了 --color 选项
            if (options.isHighlightMatch()) {
                // 使用正则表达式高亮匹配的关键字
                std::string content = result.getLineContent();
                for (const auto& keyword : options.getKeywords()) {
                    std::regex keyword_regex(keyword, options.isIgnoreCase() ? std::regex::icase : std::regex::ECMAScript);
                    content = std::regex_replace(content, keyword_regex, "\033[1;31m$&\033[0m");
                }
                std::cout << "  Content: " << content << std::endl;
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