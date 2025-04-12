#ifndef SEARCH_OPTION_H
#define SEARCH_OPTION_H

#include <string>
#include <vector>
#include <iostream>

class SearchOption {
public:
    // 构造函数
    SearchOption(const std::string& dir_path, const std::vector<std::string>& patterns, bool ignore = false, bool regex = false, bool invert = false, bool list = false, bool list_non_matching = false, bool count = false, bool output_only = false, bool highlight = false)
        : directory_path(dir_path), keywords(patterns), ignore_case(ignore), use_regex(regex), invert_match(invert), list_only(list), list_only_non_matching(list_non_matching), count_only(count), output_only_match(output_only), highlight_match(highlight) {}

    // 静态方法：解析命令行参数
    static SearchOption parseArguments(int argc, char* argv[]) {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <directory_path> [-e pattern]... [-i] [-r] [-v] [-n] [-l] [-L] [-c] [-o] [--color]" << std::endl;
            exit(1);
        }

        std::string directory_path = argv[1];
        std::vector<std::string> patterns;
        bool ignore_case = false;
        bool use_regex = false;
        bool invert_match = false;
        bool show_line_number = false;
        bool list_only = false;
        bool list_only_non_matching = false;
        bool count_only = false;
        bool output_only_match = false;
        bool highlight_match = false;

        for (int i = 2; i < argc; ++i) {
            std::string option = argv[i];
            if (option == "-e") {
                if (i + 1 < argc) {
                    patterns.push_back(argv[++i]); // 将模式添加到 patterns 列表中
                } else {
                    std::cerr << "Error: -e option requires a pattern." << std::endl;
                    exit(1);
                }
            } else if (option == "-i") {
                ignore_case = true;
            } else if (option == "-r") {
                use_regex = true;
            } else if (option == "-v") {
                invert_match = true;
            } else if (option == "-n") {
                show_line_number = true;
            } else if (option == "-l") {
                list_only = true;
            } else if (option == "-L") {
                list_only_non_matching = true;
            } else if (option == "-c") {
                count_only = true;
            } else if (option == "-o") {
                output_only_match = true;
            } else if (option == "--color") {
                highlight_match = true;
            } else {
                std::cerr << "Unknown option: " << option << std::endl;
                exit(1);
            }
        }

        if (patterns.empty()) {
            std::cerr << "Error: At least one pattern must be specified with -e." << std::endl;
            exit(1);
        }

        return SearchOption(directory_path, patterns, ignore_case, use_regex, invert_match, list_only, list_only_non_matching, count_only, output_only_match, highlight_match);
    }

    // 获取目录路径
    const std::string& getDirectoryPath() const {
        return directory_path;
    }

    // 获取所有关键词
    const std::vector<std::string>& getKeywords() const {
        return keywords;
    }

    // 是否忽略大小写
    bool isIgnoreCase() const {
        return ignore_case;
    }

    // 是否使用正则表达式
    bool isUseRegex() const {
        return use_regex;
    }

    // 是否反向匹配
    bool isInvertMatch() const {
        return invert_match;
    }

    // 是否只显示匹配的文件名
    bool isListOnly() const {
        return list_only;
    }

    // 是否只显示不包含匹配内容的文件名
    bool isListOnlyNonMatching() const {
        return list_only_non_matching;
    }

    // 是否只显示匹配的行数
    bool isCountOnly() const {
        return count_only;
    }

    // 是否只输出匹配的部分
    bool isOutputOnlyMatch() const {
        return output_only_match;
    }

    // 是否高亮匹配的关键字
    bool isHighlightMatch() const {
        return highlight_match;
    }

private:
    std::string directory_path;           // 搜索的目录路径
    std::vector<std::string> keywords;    // 搜索的关键词列表
    bool ignore_case;                     // 是否忽略大小写
    bool use_regex;                       // 是否使用正则表达式
    bool invert_match;                    // 是否反向匹配
    bool list_only;                       // 是否只显示匹配的文件名
    bool list_only_non_matching;          // 是否只显示不包含匹配内容的文件名
    bool count_only;                      // 是否只显示匹配的行数
    bool output_only_match;               // 是否只输出匹配的部分
    bool highlight_match;                 // 是否高亮匹配的关键字
};

#endif // SEARCH_OPTION_H