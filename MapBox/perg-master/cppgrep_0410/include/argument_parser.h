#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include "options.h"
#include <optional>
#include <vector>
#include <string>

class ArgumentParser {
public:
    // 解析参数。成功时返回options，出错或请求帮助时返回nullopt
    std::optional<SearchOptions> parse(int argc, char* argv[]);

private:
    void showUsage(const char* program_name);
};

#endif // ARGUMENT_PARSER_H