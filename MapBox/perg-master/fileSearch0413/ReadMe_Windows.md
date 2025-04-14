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

  -r            Enables regular expression matching.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt "[a-zA-Z]+" -r

  -E            Uses extended regular expressions (equivalent to egrep).
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt "hello|world" -E

  -v            Inverts the match, displaying lines that do not match the specified patterns.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -v

  -n            Displays line numbers for matching lines.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -n

  -l            Lists only the names of files containing matches.
                Example:
                  .\fileSearch.exe ..\..\test_dir hello -l

  -L            Lists only the names of files that do not contain matches.
                Example:
                  .\fileSearch.exe ..\..\test_dir hello -L

  -c            Displays the count of matching lines for each file.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -c

  -o            Outputs only the matching part of the line.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello -o

  --color[=auto] Highlights matching keywords in the output. The auto option enables color only when the output is directed to a terminal.
                Example:
                  .\fileSearch.exe ..\..\test_dir\file1.txt hello --color

## Notes
- Multiple options can be combined to refine the search.
- Regular expressions must be properly escaped depending on the shell being used.
- Ensure the file or directory path and permissions are correct before running the tool.