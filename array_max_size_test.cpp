#include <iostream>
#include <array>

int main() {
    try {
        // Attempt to create a very large std::array
        constexpr size_t LARGE_SIZE = 100000000; // 100 million elements
        std::array<int, LARGE_SIZE> largeArray;
        std::cout << "Successfully allocated array with " << LARGE_SIZE << " elements." << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred while allocating array." << std::endl;
    }

    return 0;
}
