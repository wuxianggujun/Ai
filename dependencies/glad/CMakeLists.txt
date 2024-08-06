cmake_minimum_required(VERSION 3.10)
project(glad LANGUAGES C)

add_library(${PROJECT_NAME} STATIC glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
