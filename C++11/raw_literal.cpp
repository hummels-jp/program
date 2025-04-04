#include <iostream>
#include <string>

int main() {
    // 使用原始字符串字面量
    std::string rawString = R"(这是一个原始字符串字面量，
它可以包含换行符和特殊字符，比如 \n 和 \t，
而不需要使用转义序列。)";

    std::cout << "原始字符串内容：" << std::endl;
    std::cout << rawString << std::endl;

    // 使用带分隔符的原始字符串字面量
    std::string rawStringWithDelimiter = R"delimiter(这是一个带分隔符的原始字符串，
它可以包含括号，比如 ()，而不会结束字符串。)delimiter";

    std::cout << "带分隔符的原始字符串内容：" << std::endl;
    std::cout << rawStringWithDelimiter << std::endl;

    return 0;
}