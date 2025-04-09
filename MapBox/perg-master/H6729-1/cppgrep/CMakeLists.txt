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

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(cppgrep ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(cppgrep PRIVATE Threads::Threads)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
        target_link_libraries(cppgrep PRIVATE stdc++fs)
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
        target_link_libraries(cppgrep PRIVATE c++fs)
    endif()
endif()

install(TARGETS cppgrep DESTINATION bin)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")