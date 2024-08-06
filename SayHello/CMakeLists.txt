# 确保SOURCE_FILES变量包含所有源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCE_FILES)
# 为SayHello目标添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

