#ifndef SEARCH_OPTION_H
#define SEARCH_OPTION_H

#include <string>
#include <vector>
#include <iostream>

class SearchOption {
public:
    // Constructor
    SearchOption(const std::string& dir_path, const std::vector<std::string>& patterns, bool ignore = false, bool regex = false, bool extended = false, bool invert = false, bool list = false, bool list_non_matching = false, bool count = false, bool output_only = false, bool highlight = false)
        : directory_path(dir_path), keywords(patterns), ignore_case(ignore), use_regex(regex), extended_regex(extended), invert_match(invert), list_only(list), list_only_non_matching(list_non_matching), count_only(count), output_only_match(output_only), highlight_match(highlight) {}

    // Static method: Parse command-line arguments
    static SearchOption parseArguments(int argc, char* argv[]) {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <directory_path> [-e pattern]... [-i] [-r] [-E] [-v] [-n] [-l] [-L] [-c] [-o] [--color]" << std::endl;
            exit(1);
        }

        std::string directory_path = argv[1];
        std::vector<std::string> patterns;
        bool ignore_case = false;
        bool use_regex = false;
        bool extended_regex = false;
        bool invert_match = false;
        bool show_line_number = false;
        bool list_only = false;
        bool list_only_non_matching = false;
        bool count_only = false;
        bool output_only_match = false;
        bool highlight_match = false;

        for (int i = 2; i < argc; ++i) {
            std::string option = argv[i];
            if (option == "-e") {
                if (i + 1 < argc) {
                    patterns.push_back(argv[++i]); // Add the pattern to the patterns list
                } else {
                    std::cerr << "Error: -e option requires a pattern." << std::endl;
                    exit(1);
                }
            } else if (option == "-i") {
                ignore_case = true;
            } else if (option == "-r") {
                use_regex = true;
            } else if (option == "-E") {
                extended_regex = true;
            } else if (option == "-v") {
                invert_match = true;
            } else if (option == "-n") {
                show_line_number = true;
            } else if (option == "-l") {
                list_only = true;
            } else if (option == "-L") {
                list_only_non_matching = true;
            } else if (option == "-c") {
                count_only = true;
            } else if (option == "-o") {
                output_only_match = true;
            } else if (option == "--color") {
                highlight_match = true;
            } else {
                std::cerr << "Unknown option: " << option << std::endl;
                exit(1);
            }
        }

        if (patterns.empty()) {
            std::cerr << "Error: At least one pattern must be specified with -e." << std::endl;
            exit(1);
        }

        return SearchOption(directory_path, patterns, ignore_case, use_regex, extended_regex, invert_match, list_only, list_only_non_matching, count_only, output_only_match, highlight_match);
    }

    // Get the directory path
    const std::string& getDirectoryPath() const {
        return directory_path;
    }

    // Get all keywords
    const std::vector<std::string>& getKeywords() const {
        return keywords;
    }

    // Check if case-insensitive matching is enabled
    bool isIgnoreCase() const {
        return ignore_case;
    }

    // Check if regular expressions are enabled
    bool isUseRegex() const {
        return use_regex;
    }

    // Check if extended regular expressions are enabled
    bool isExtendedRegex() const {
        return extended_regex;
    }

    // Set the extended regular expression option
    void setExtendedRegex(bool extended) {
        extended_regex = extended;
    }

    // Check if inverted matching is enabled
    bool isInvertMatch() const {
        return invert_match;
    }

    // Check if only matching file names should be displayed
    bool isListOnly() const {
        return list_only;
    }

    // Check if only non-matching file names should be displayed
    bool isListOnlyNonMatching() const {
        return list_only_non_matching;
    }

    // Check if only the count of matching lines should be displayed
    bool isCountOnly() const {
        return count_only;
    }

    // Check if only the matching part of the line should be output
    bool isOutputOnlyMatch() const {
        return output_only_match;
    }

    // Check if matching keywords should be highlighted
    bool isHighlightMatch() const {
        return highlight_match;
    }

private:
    std::string directory_path;           // The directory path to search
    std::vector<std::string> keywords;    // The list of keywords to search for
    bool ignore_case;                     // Whether to ignore case
    bool use_regex;                       // Whether to use regular expressions
    bool extended_regex;                  // Whether to use extended regular expressions
    bool invert_match;                    // Whether to invert the match
    bool list_only;                       // Whether to display only matching file names
    bool list_only_non_matching;          // Whether to display only non-matching file names
    bool count_only;                      // Whether to display only the count of matching lines
    bool output_only_match;               // Whether to output only the matching part of the line
    bool highlight_match;                 // Whether to highlight matching keywords
};

#endif // SEARCH_OPTION_H