add_library(AiCore "src/AiCore.cpp" "src/Painter.cpp"    "include/Shader.h" "include/Texture.h"   "include/Object.h" "src/Object.cpp" "include/Camera.h" "include/Mesh.h" "src/Mesh.cpp")

#AiCore
include_directories("${PROJECT_SOURCE_DIR}/AiCore/include")

# ...
target_link_libraries(AiCore PRIVATE 
					  glfw
					  glad
					  opengl32.lib
					  )