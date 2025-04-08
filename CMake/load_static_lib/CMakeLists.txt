# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(load_static_library)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
# file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# Add header files (if needed)
# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add library
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Add object library
# 添加静态库
link_libraries(calculator)

# 添加库文件路径
# 这里的路径是相对于 CMakeLists.txt 文件的路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 设置可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 编译可执行程序
add_executable(load_static_library ${SOURCES})





# Include directories (if needed)
# target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link libraries (if needed)
# target_link_libraries(${PROJECT_NAME} PRIVATE some_library)