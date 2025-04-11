#include <iostream>
#include <regex>
#include <string>
#include "regex_search.h"

int regex_search_demo() {
    std::string email = "example@example.com";
    std::regex email_pattern(R"((\w+)(\.?\w+)*@(\w+)(\.\w+)+)");

    if (std::regex_search(email, email_pattern)) {
        std::cout << "Valid email: " << email << std::endl;
    } else {
        std::cout << "Invalid email: " << email << std::endl;
    }

    return 0;
}