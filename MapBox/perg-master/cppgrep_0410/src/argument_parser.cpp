#include "argument_parser.h"
#include <iostream>
#include <string>
#include <thread> // For hardware_concurrency

std::optional<SearchOptions> ArgumentParser::parse(int argc, char* argv[]) {
    SearchOptions options;
    int arg_index = 1;

    // check the options
    while (arg_index < argc && argv[arg_index][0] == '-') 
    {
        std::string option = argv[arg_index];
        // -i hello ../test_dir/file1.txt
        if (option == "-i") {
            options.ignore_case = true;
        } else if (option == "-r") {
            options.use_regex = true;
        } else if (option == "-h") {
            showUsage(argv[0]);
            return std::nullopt;  // return nullopt to indicate help requested
        } else {
            std::cerr << "Unknown option: " << option << std::endl;
            showUsage(argv[0]);
            return std::nullopt; 
        }
        arg_index++;
    }

    if (argc - arg_index != 2) {
        std::cerr << "Error: Insufficient or too many arguments" << std::endl;
        showUsage(argv[0]);
        return std::nullopt; // return nullopt to indicate error
    }

    options.query = argv[arg_index++];
    options.directory = argv[arg_index];

    options.num_threads = std::thread::hardware_concurrency(); // Get the number of hardware threads
    if (options.num_threads == 0) {
        options.num_threads = 2;
        std::cerr << "Warning: Cannot detect hardware concurrency. Using "
                  << options.num_threads << " threads." << std::endl;
    }

    return options;
}

// Show usage information
// This function is called when the user requests help or when there are errors in the arguments
// It prints the usage information to the standard output
// The usage information includes the program name, options, and a brief description of each option
void ArgumentParser::showUsage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [options] <query> <directory path>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i        Ignore case" << std::endl;
    std::cout << "  -r        Use regular expression for search" << std::endl;
    std::cout << "  -h        Show this help information" << std::endl;
}