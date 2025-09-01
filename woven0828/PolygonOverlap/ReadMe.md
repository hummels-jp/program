# PolygonOverlap User Guide

## Build Instructions

Recommended: use CMake

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

Or compile directly with g++ (requires C++11 or above):

```sh
g++ -std=c++11 -pthread -o PolygonOverlap main.cpp PolygonFilter.cpp ... # other source files omitted
```

## Build with MinGW (g++) on Windows

If you have installed MinGW-w64 and want to use g++ instead of Visual Studio:

1. Open PowerShell and go to the build directory:
   ```powershell
   mkdir build
   cd build
   ```
2. Run CMake and specify the MinGW generator:
   ```powershell
   cmake -G "MinGW Makefiles" ..
   mingw32-make
   ```
   Or (if g++ is in your PATH, you can use make directly):
   ```powershell
   cmake -G "MinGW Makefiles" ..
   make
   ```

> Note: If you do not add -G "MinGW Makefiles", CMake will use Visual Studio as the default generator.
>
> If you need to specify the path to g++.exe, you can set it at the top of CMakeLists.txt:
> ```cmake
> set(CMAKE_C_COMPILER "gcc" CACHE STRING "" FORCE)
> set(CMAKE_CXX_COMPILER "g++" CACHE STRING "" FORCE)
> ```

## Usage

The program supports both single-threaded and multi-threaded modes. Command format:

```
./PolygonOverlap <input_json> <output_json> <single|multi> [min_threads]
```

- `<input_json>`: Path to the input JSON file containing polygon data
- `<output_json>`: Path to the output JSON file
- `<single|multi>`: Processing mode, `single` for single-threaded, `multi` for multi-threaded
- `[min_threads]`: Minimum number of threads in multi-threaded mode (optional, default is 2)

### Examples

Single-threaded:
```
./PolygonOverlap ../input/convex_hulls_100.json ../output/output_100.json single
```

Multi-threaded (minimum 8 threads):
```
./PolygonOverlap ../input/convex_hulls_1000.json ../output/output_1000.json multi 8
```

## Input/Output Format

- Input file: JSON format, contains polygon vertex information.
- Output file: JSON format, contains filtered polygons and their properties.

## Dependencies

- C++11 or higher
- CMake 3.10+
- nlohmann/json (or compatible JSON library)

## Notes

- The program will automatically create the output directory if it does not exist.
- In multi-threaded mode, the thread pool dynamically adjusts the number of worker threads based on workload.
- The program prints the total execution time (in milliseconds) after completion.

JSON File Visualization Tool
..\ResultCheck02\x64\Release\ResultCheck02.exe
1. To verify the correctness of the algorithm, an MFC-based JSON file visualization tool was developed.
2. `OpenInputJson` can open and visualize the original input JSON file.
3. `OpenOutputJson` can open and visualize the output JSON file after filtering.
