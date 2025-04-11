#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <cctype> // For std::tolower, isprint, isspace

namespace Utils {
    // Convert a string to lowercase
    inline std::string to_lower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        return str;
    }

    // Check if a string is likely binary content
    inline bool is_likely_binary(const std::string& str) {
        // Check if the first 1024 characters contain null characters
        const size_t check_length = std::min(str.length(), size_t(1024));
        return std::any_of(str.begin(), str.begin() + check_length,
                          [](char c) { return c == '\0'; });
    }

} // namespace Utils

#endif // UTILS_H