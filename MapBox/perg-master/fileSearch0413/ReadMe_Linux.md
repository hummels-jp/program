# fileSearch Tool Documentation (Linux Version)

## Build
Make sure your system has the GCC compiler and CMake installed.  
Go to the `../build` directory and run the following commands:
```bash
rm -fr ./*
cmake ..
make
```

# Usage:
Navigate to the bin directory
```bash
cd ../bin/linux
./fileSearch <file_or_directory> [options]
```

# Options:
  -i            Ignores case when matching patterns.
                Example:
                  ./fileSearch ../../test_dir/file1.txt hello -i

  -n            Displays line numbers for matching lines.
                Example:
                  ./fileSearch ../../test_dir/file1.txt hello -n

  -l            Lists only the names of files containing matches.
                Example:
                  ./fileSearch ../../test_dir hello -l

  -c            Displays the count of matching lines for each file.
                Example:
                  ./fileSearch ../../test_dir/file1.txt hello -c

  -o            Outputs only the matching part of the line.
                Example:
                  ./fileSearch ../../test_dir/file1.txt hello -o

  -v            Inverts the match, displaying lines that do not match the specified patterns.
                Example:
                  ./fileSearch ../../test_dir/file1.txt hello -v                  

# Notes:
- Multiple options can be combined to refine the search.
- Regular expressions must be properly escaped depending on the shell being used.
- Ensure the file or directory path and permissions are correct before running the tool.