#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include "options.h"
#include <optional>
#include <vector>
#include <string>

class ArgumentParser {
public:
    // Parse arguments. Returns options on success, or nullopt on error or help request
    std::optional<SearchOptions> parse(int argc, char* argv[]);

private:
    void showUsage(const char* program_name);
};

#endif // ARGUMENT_PARSER_H