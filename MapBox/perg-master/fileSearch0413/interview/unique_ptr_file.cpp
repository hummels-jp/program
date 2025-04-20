#include <iostream>
#include <memory>
#include <cstdio> // For FILE operations

// Custom Deletor using a normal function
void fileDeletor(FILE* file) {
    if (file) {
        std::cout << "Closing file (normal function)..." << std::endl;
        fclose(file);
    }
}

// Custom Deletor using a functor (function object)
struct FunctorDeletor {
    void operator()(FILE* file) const {
        if (file) {
            std::cout << "Closing file (functor)..." << std::endl;
            fclose(file);
        }
    }
};

// Class with member function and static member function as Deletor
class FileManager {
public:
    // Member function as Deletor
    void memberDeletor(FILE* file) const {
        if (file) {
            std::cout << "Closing file (member function)..." << std::endl;
            fclose(file);
        }
    }

    // Static member function as Deletor
    static void staticDeletor(FILE* file) {
        if (file) {
            std::cout << "Closing file (static member function)..." << std::endl;
            fclose(file);
        }
    }
};

int main() {
    try {
        // Using a normal function as a custom deletor
        std::unique_ptr<FILE, decltype(&fileDeletor)> filePtr1(fopen("example1.txt", "w"), fileDeletor);
        if (!filePtr1) {
            throw std::runtime_error("Failed to open file: example1.txt");
        }
        fprintf(filePtr1.get(), "Hello, World from normal function deletor!\n");

        // File will be automatically closed when filePtr1 goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        // Using a functor as a custom deletor
        std::unique_ptr<FILE, FunctorDeletor> filePtr2(fopen("example2.txt", "w"), FunctorDeletor());
        if (!filePtr2) {
            throw std::runtime_error("Failed to open file: example2.txt");
        }
        fprintf(filePtr2.get(), "Hello, World from functor deletor!\n");

        // File will be automatically closed when filePtr2 goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        // Using a member function as a custom deletor
        FileManager fileManager;
        auto memberDeletor = [&fileManager](FILE* file) { fileManager.memberDeletor(file); };
        std::unique_ptr<FILE, decltype(memberDeletor)> filePtr3(fopen("example3.txt", "w"), memberDeletor);
        if (!filePtr3) {
            throw std::runtime_error("Failed to open file: example3.txt");
        }
        fprintf(filePtr3.get(), "Hello, World from member function deletor!\n");

        // File will be automatically closed when filePtr3 goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        // Using a static member function as a custom deletor
        std::unique_ptr<FILE, decltype(&FileManager::staticDeletor)> filePtr4(fopen("example4.txt", "w"), FileManager::staticDeletor);
        if (!filePtr4) {
            throw std::runtime_error("Failed to open file: example4.txt");
        }
        fprintf(filePtr4.get(), "Hello, World from static member function deletor!\n");

        // File will be automatically closed when filePtr4 goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}