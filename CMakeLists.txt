# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("Ai")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#AiCore
include_directories("${PROJECT_SOURCE_DIR}/AiCore/include")
#Config glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(3rd_party/glfw)
include_directories(3rd_party/glfw/include)
LIST(APPEND LIBS glfw ${GLFW_LIBRARIES})
#Config glad
include_directories("${PROJECT_SOURCE_DIR}/3rd_party/glad/include")
#Config glm
include_directories("${PROJECT_SOURCE_DIR}/3rd_party/glm")
#Config stb_image
include_directories("${PROJECT_SOURCE_DIR}/3rd_party/stb")
#Config assimp
# option(BUILD_SHARED_LIBS OFF)
# add_subdirectory(3rd_party/assimp)
# include_directories(3rd_party/assimp/include)


set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY ${SOURCE_DIR} DESTINATION ${TARGET_DIR})

# 将源代码添加到此项目的可执行文件。
add_executable (Ai "main.cpp" "AiCore/src/AiCore.cpp")

target_include_directories(Ai PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Include"
                          )

target_link_directories(Ai PRIVATE
						"${PROJECT_SOURCE_DIR}/Libs"
						)

add_subdirectory("3rd_party/glad")
add_subdirectory("SayHello")
add_subdirectory("AiCore")

target_link_libraries(Ai PRIVATE 
					  glfw
					  glad
					  opengl32.lib
					  AiCore
					  )

