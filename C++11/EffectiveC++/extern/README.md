# README.md

# Extern Example Project

This project demonstrates the use of global variables in C++ using separate source and header files. It includes a simple application that modifies and displays global variables.

## Project Structure

```
extern
├── global.cpp      # Definitions of global variables
├── global.h       # Declarations of global variables
├── main.cpp       # Entry point of the application
├── CMakeLists.txt # CMake configuration file
└── README.md      # Project documentation
```

## Building the Project

To build the project, you need to have CMake installed. Follow these steps:

1. Open a terminal (Command Prompt on Windows or Terminal on Linux).
2. Navigate to the project directory:
   ```
   cd path/to/extern
   ```
3. Create a build directory:
   ```
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   cmake --build .
   ```

## Running the Application

After building the project, you can run the application with the following command:

```
./ExternExample   # On Linux
ExternExample.exe # On Windows
```

This will display the initial and updated values of the global variables `global_name` and `global_age`.