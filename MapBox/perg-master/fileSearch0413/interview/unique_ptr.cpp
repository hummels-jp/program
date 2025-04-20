#include <iostream>
#include <memory> // For std::unique_ptr
#include <fstream> // For file operations

class MyClass {
public:
    MyClass(int value) : value(value) {
        std::cout << "Constructor called for value: " << value << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called for value: " << value << std::endl;
    }

    void display() const {
        std::cout << "Value: " << value << std::endl;
    }

private:
    int value;
};

class FileWrapper {
private:
    std::fstream file;

public:
    // Constructor: Open the file
    FileWrapper(const std::string& fileName, std::ios::openmode mode) {
        file.open(fileName, mode);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + fileName);
        }
        std::cout << "File opened: " << fileName << std::endl;
    }

    // Destructor: Close the file
    ~FileWrapper() {
        if (file.is_open()) {
            file.close();
            std::cout << "File closed." << std::endl;
        }
    }

    // Write to the file
    void write(const std::string& data) {
        if (file.is_open()) {
            file << data << std::endl;
        } else {
            throw std::runtime_error("File is not open for writing.");
        }
    }

    // Read from the file
    void read() {
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::cout << line << std::endl;
            }
        } else {
            throw std::runtime_error("File is not open for reading.");
        }
    }
};

int main() {
    try {
        // Create a unique_ptr to manage the FileWrapper object
        std::unique_ptr<FileWrapper> filePtr = std::make_unique<FileWrapper>("example.txt", std::ios::out);
        filePtr->write("Hello, World!");
        filePtr->write("This is a test file.");

        // File will be automatically closed when filePtr goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        // Reopen the file in read mode
        std::unique_ptr<FileWrapper> filePtr = std::make_unique<FileWrapper>("example.txt", std::ios::in);
        filePtr->read();

        // File will be automatically closed when filePtr goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}