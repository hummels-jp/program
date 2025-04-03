#include <iostream>
#include <string>
#include <functional>

// 通用模板
template <typename T>
size_t calculateHash(const T& value) {
    std::hash<T> hasher;
    return hasher(value);
}

// 特化模板：针对const char*类型
template <>
size_t calculateHash<const char*>(const char* const& value) {
    std::hash<std::string> hasher;
    return hasher(std::string(value));
}

// 特化模板：针对int类型
template <>
size_t calculateHash<int>(const int& value) {
    return static_cast<size_t>(value * 2654435761 % 4294967296); // Knuth's multiplicative hash
}

// 特化模板：针对long类型
template <>
size_t calculateHash<long>(const long& value) {
    return static_cast<size_t>(value ^ (value >> 32)); // Simple XOR-based hash
}

// 特化模板：针对double类型
template <>
size_t calculateHash<double>(const double& value) {
    std::hash<double> hasher;
    return hasher(value);
}

int main() {
    int intValue = 42;
    long longValue = 1234567890L;
    double doubleValue = 3.14159;
    std::string strValue = "Hello, World!";
    const char* cStrValue = "Hello, C-String!";

    std::cout << "Hash of int: " << calculateHash(intValue) << std::endl;
    std::cout << "Hash of long: " << calculateHash(longValue) << std::endl;
    std::cout << "Hash of double: " << calculateHash(doubleValue) << std::endl;
    std::cout << "Hash of std::string: " << calculateHash(strValue) << std::endl;
    std::cout << "Hash of const char*: " << calculateHash(cStrValue) << std::endl;

    return 0;
}
