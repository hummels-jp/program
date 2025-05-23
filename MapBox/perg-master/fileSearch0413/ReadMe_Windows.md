# fileSearch Tool Documentation (Windows Version)

## Build
Make sure you have Git Bash installed and MinGW configured.  
Go to the `../build` directory and run the following commands:
```bash
rm -r ./*
cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake ..
make
```

## Usage
Navigate to the bin directory:
```bash
cd ../bin/windows
.\fileSearch.exe <file_or_directory> [options]
```

## Options
  -i            Ignores case when matching patterns.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -i

  -n            Displays line numbers for matching lines.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -n

  -l            Lists only the names of files containing matches.
                Example:
                  .\fileSearch.exe ..\..\test_dir hello -l

  -c            Displays the count of matching lines for each file.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -c

  -o            Outputs only the matching part of the line.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -o

  -v            Inverts the match, displaying lines that do not match the specified patterns.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -v                  


## Notes
- Multiple options can be combined to refine the search.
- Regular expressions must be properly escaped depending on the shell being used.
- Ensure the file or directory path and permissions are correct before running the tool.