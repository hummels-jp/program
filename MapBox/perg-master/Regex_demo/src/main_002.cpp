#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string input = "Name: John";

    std::regex pattern(R"(Name:\s+(\w+))");
    std::smatch match;

    if (std::regex_match(input, match, pattern)) {
        std::cout << "Captured name: " << match[1] << std::endl;
    } else {
        std::cout << "No match." << std::endl;
    }

    return 0;
}
