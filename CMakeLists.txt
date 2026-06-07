cmake_minimum_required(VERSION 3.20)
project(md2html LANGUAGES CXX)

# 要求 C++20（GCC 16.1.0 完整支持）
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 静态链接，避免运行时 DLL 依赖
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# 源文件
add_executable(md2html
    src/main.cpp
    src/utils.cpp
)

# 头文件搜索路径
target_include_directories(md2html PRIVATE src)
