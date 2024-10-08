﻿# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.8)

project(Ai)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ON 就是SayHello 需要重置cmake缓存
set(AI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(AI_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources")

# 确保目标资源目录存在
file(MAKE_DIRECTORY ${AI_BINARY_DIR})

add_subdirectory(dependencies)
add_subdirectory(AiCore)

# 确保main.cpp存在于项目的根目录下
add_executable(${PROJECT_NAME} main.cpp)
# 链接core库，假设core是一个库
target_link_libraries(${PROJECT_NAME} PRIVATE AiCore)

# 定义一个自定义目标，每次构建时拷贝资源目录
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${AI_SOURCE_DIR}"
        "${AI_BINARY_DIR}"
        COMMENT "Copying resources directory to binary directory"
)

# 确保在生成目标之前先执行资源拷贝
add_dependencies(${PROJECT_NAME} copy_resources)
