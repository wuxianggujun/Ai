cmake_minimum_required(VERSION 3.10)
project(dependencies LANGUAGES CXX)

# 添加子项目
add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm/glm)


