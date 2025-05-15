#include <iostream>
#include <fstream>
#include <string>

bool isBinaryFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        return false;
    }

    char buffer[512];
    file.read(buffer, sizeof(buffer));
    std::streamsize bytesRead = file.gcount();

    for (std::streamsize i = 0; i < bytesRead; ++i) {
        // Check for non-printable characters (excluding common whitespace characters)
        if (buffer[i] < 0x20 && buffer[i] != '\t' && buffer[i] != '\n' && buffer[i] != '\r') {
            return true; // File is binary
        }
    }

    return false; // File is text
}

int main() {
    std::string filePath;
    std::cout << "Enter the file path: ";
    std::cin >> filePath;

    if (isBinaryFile(filePath)) {
        std::cout << "The file is a binary file." << std::endl;
    } else {
        std::cout << "The file is a text file." << std::endl;
    }

    return 0;
}