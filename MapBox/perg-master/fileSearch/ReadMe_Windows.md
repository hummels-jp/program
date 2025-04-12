# fileSearch Tool Documentation
# build
# install git bash
# download MinGW，add the gcc g++ directory path to environment variable
# warning: notice the gcc file path in file ./toolchain-mingw.cmake, you should change to your path
# go the ./build directory and run the command as follow
# cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake ..
# make


# Usage:
# enter the bin directory ../bin/windows
# .\fileSearch.exe <file_or_directory> [options]

# Options:
#   -e PATTERN    Specifies a search pattern. This option can be used multiple times to specify multiple patterns.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e hello 
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e hello -e world

#   -i            Ignores case when matching patterns.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e hello -i

#   -r            Enables regular expression matching.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e "[a-zA-Z]+" -r

#   -E            Uses extended regular expressions (equivalent to egrep).
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e "hello|world" -E

#   -v            Inverts the match, displaying lines that do not match the specified patterns.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e hello -v

#   -n            Displays line numbers for matching lines.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e hello -n

#   -l            Lists only the names of files containing matches.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir -e hello -l

#   -L            Lists only the names of files that do not contain matches.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir -e hello -L

#   -c            Displays the count of matching lines for each file.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e hello -c

#   -o            Outputs only the matching part of the line.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e hello -o

#   --color[=auto] Highlights matching keywords in the output. The auto option enables color only when the output is directed to a terminal.
#                 Example:
#                   .\fileSearch.exe ..\..\test_dir\file1.txt -e hello --color

# Notes:
# - Multiple options can be combined to refine the search.
# - Regular expressions must be properly escaped depending on the shell being used.
# - Ensure the file or directory path and permissions are correct before running the tool.