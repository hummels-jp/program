cmake_minimum_required(VERSION 3.10)
project(OpenMP_Test CXX)

# 查找 OpenMP 包
find_package(OpenMP REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 链接可执行文件
add_executable(openmp_example ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# 设置 C++ 标准为 C++11
# 这里的 CXX_STANDARD 和 CXX_STANDARD_REQUIRED 是 CMake 的属性，用于指定 C++ 标准和是否强制要求该标准
# CXX_EXTENSIONS 属性用于指定是否使用编译器的扩展
set_target_properties(openmp_example PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link OpenMP to the target
target_link_libraries(openmp_example PRIVATE OpenMP::OpenMP_CXX)
