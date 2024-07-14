# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("Ai")

# 将源代码添加到此项目的可执行文件。

add_executable (Ai "main.cpp")

target_include_directories(Ai PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Include"
                          )

target_link_directories(Ai PRIVATE
						"${PROJECT_SOURCE_DIR}/Libs"
						)

add_subdirectory("SayHello")
