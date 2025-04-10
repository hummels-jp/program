#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <cctype> // For std::tolower, isprint, isspace

namespace Utils {
    // 将字符串转换为小写
    inline std::string to_lower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        return str;
    }

    // 检查字符串是否可能是二进制内容
    inline bool is_likely_binary(const std::string& str) {
        // 检查前面1024个字符中是否包含空字符
        const size_t check_length = std::min(str.length(), size_t(1024));
        return std::any_of(str.begin(), str.begin() + check_length,
                          [](char c) { return c == '\0'; });
    }

} // namespace Utils

#endif // UTILS_H