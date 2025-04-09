#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main() {
    std::string email = "example@test.com";
    
    std::regex pattern(R"(\w+@\w+\.\w+)");
    
    if (std::regex_match(email, pattern)) {
        std::cout << "valid email " << std::endl;
    } else {
        std::cout << "invalid email" << std::endl;
    }

    return 0;
}
