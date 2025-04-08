# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(CMake001)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找源文件，可以使用 GLOB 或 GLOB_RECURSE 来查找文件
# GLOB: 查找当前目录下的所有源文件
# GLOB_RECURSE: 递归查找当前目录及子目录下的所有源文件

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
message("SOURCES: ${SOURCES}")
if(SOURCES AND SOURCES STREQUAL "")
	message(WARNING "No source files found in SOURCES.")
else()
	list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")
endif()
message("SOURCES: ${SOURCES}")
# file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# Add header files (if needed)
# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

set(temp "helllo world")
set(temp1 "${temp} ${SOURCES}")
message("temp: ${temp}")
message("temp1: ${temp1}")

list(APPEND temp "111" "222")
message("temp: ${temp}")

# Add library
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Add shared library
# add_library(calculator SHARED ${SOURCES})

# Add static library
# add_library(calculator STATIC ${SOURCES})

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Add executable
#add_executable(CMakeTest001 ${SOURCES})



# Include directories (if needed)
# target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link libraries (if needed)
# target_link_libraries(${PROJECT_NAME} PRIVATE some_library)