#include <iostream>

int main() {
    // 使用原始字符串字面量
    std::string raw_string = R"(This is a raw string literal.
It can span multiple lines.
Special characters like \n or \" don't need escaping.
You can even include parentheses: () or quotes: " without issues.)";

    std::cout << "Raw String Literal Example:\n" << raw_string << std::endl;

    return 0;
}