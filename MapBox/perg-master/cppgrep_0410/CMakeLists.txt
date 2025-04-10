cmake_minimum_required(VERSION 3.12)
project(cppgrep VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /EHsc)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 列出所有.cpp源文件
set(SOURCES
    main.cpp
    grepper.cpp
    argument_parser.cpp
    directory_walker.cpp
    file_searcher.cpp
    # 以下头文件没有对应的.cpp文件：utils.h, options.h, result.h, thread_safe_queue.h
)

add_executable(cppgrep ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(cppgrep PRIVATE Threads::Threads)

# 文件系统链接逻辑（对于GCC < 9, Clang < 9很重要）
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
        message(STATUS "GNU编译器 < 9.0，链接stdc++fs")
        target_link_libraries(cppgrep PRIVATE stdc++fs)
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Clang版本可能因底层LLVM/libc++而异
    # 根据目标Clang版本调整版本检查
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0) # 针对老版本Clang的示例检查
         message(STATUS "Clang编译器 < 7.0，链接c++fs")
         target_link_libraries(cppgrep PRIVATE c++fs)
    endif()
endif()

install(TARGETS cppgrep DESTINATION bin)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")