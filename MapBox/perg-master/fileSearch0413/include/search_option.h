#ifndef SEARCH_OPTION_H
#define SEARCH_OPTION_H

#include <string>

class SearchOption {
public:
    // Constructor
    // Parameters:
    // - keyword: The keyword to search for.
    // - case_sensitive: If true, the search is case-sensitive. Default is true.
    // - invert_match: If true, matches are inverted (non-matching lines are shown). Default is false.
    // - show_line_number: If true, line numbers are displayed with matches. Default is false.
    // - list_only: If true, only file names containing matches are listed. Default is false.
    // - count_only: If true, only the count of matching lines is displayed. Default is false.
    // - only_match: If true, only the matched strings are displayed. Default is false.
    // - use_regex: If true, the keyword is treated as a regular expression. Default is false.
    SearchOption(const std::string& keyword, 
                 bool case_sensitive = true, 
                 bool invert_match = false, 
                 bool show_line_number = false, 
                 bool list_only = false, 
                 bool count_only = false, 
                 bool only_match = false, 
                 bool use_regex = false)
        : keyword(keyword), 
          case_sensitive(case_sensitive), 
          invert_match(invert_match), 
          show_line_number(show_line_number), 
          list_only(list_only), 
          count_only(count_only), 
          only_match(only_match), 
          use_regex(use_regex) {}

    // Get the keyword
    const std::string& getKeyword() const {
        return keyword;
    }

    // Check if the search is case-sensitive
    bool isCaseSensitive() const {
        return case_sensitive;
    }

    // Check if the search is inverted
    bool isInvertMatch() const {
        return invert_match;
    }

    // Check if line numbers should be shown
    bool isShowLineNumber() const {
        return show_line_number;
    }

    // Check if only file names should be listed
    bool isListOnly() const {
        return list_only;
    }

    // Check if only the count of matching lines should be shown
    bool isCountOnly() const {
        return count_only;
    }

    // Check if only the matched string should be shown
    bool isOnlyMatch() const {
        return only_match;
    }

    // Check if regex should be used
    bool isUseRegex() const {
        return use_regex;
    }

    // Set the keyword
    void setKeyword(const std::string& new_keyword) {
        keyword = new_keyword;
    }

    // Set case sensitivity
    void setCaseSensitive(bool is_case_sensitive) {
        case_sensitive = is_case_sensitive;
    }

    // Set invert match
    void setInvertMatch(bool is_invert_match) {
        invert_match = is_invert_match;
    }

    // Set show line number
    void setShowLineNumber(bool is_show_line_number) {
        show_line_number = is_show_line_number;
    }

    // Set list only
    void setListOnly(bool is_list_only) {
        list_only = is_list_only;
    }

    // Set count only
    void setCountOnly(bool is_count_only) {
        count_only = is_count_only;
    }

    // Set only match
    void setOnlyMatch(bool is_only_match) {
        only_match = is_only_match;
    }

    // Set use regex
    void setUseRegex(bool is_use_regex) {
        use_regex = is_use_regex;
    }

private:
    std::string keyword;         // Keyword to search for
    bool case_sensitive;         // Case sensitivity flag
    bool invert_match;           // Invert match flag
    bool show_line_number;       // Show line number flag
    bool list_only;              // List only matching file names
    bool count_only;             // Show only the count of matching lines
    bool only_match;             // Show only the matched string
    bool use_regex;              // Use regex for matching
};

#endif // SEARCH_OPTION_H