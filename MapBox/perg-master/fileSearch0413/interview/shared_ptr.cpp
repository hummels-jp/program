#include <iostream>
#include <memory>
#include <cstdio> // For FILE operations

// Custom Deletor for FILE*
void fileDeletor(FILE* file) {
    if (file) {
        std::cout << "Closing file..." << std::endl;
        fclose(file);
    }
}

int main() {
    try {
        // Create a shared_ptr with a custom deletor to manage FILE*
        std::shared_ptr<FILE> filePtr(fopen("example.txt", "w"), fileDeletor);
        if (!filePtr) {
            throw std::runtime_error("Failed to open file.");
        }

        // Write to the file
        fprintf(filePtr.get(), "Hello, World from shared_ptr!\n");
        fprintf(filePtr.get(), "This is a test file managed by shared_ptr.\n");

        // Share ownership of the file resource
        std::shared_ptr<FILE> filePtr2 = filePtr;
        fprintf(filePtr2.get(), "Another line written using shared_ptr.\n");

        // File will be automatically closed when the last shared_ptr goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}