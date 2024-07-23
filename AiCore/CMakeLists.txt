add_library(AiCore "src/AiCore.cpp" "src/Painter.cpp"    "include/Shader.h" "include/Texture.h"   "include/Object.h" "src/Object.cpp")

# ...
target_link_libraries(AiCore PRIVATE 
					  glfw
					  glad
					  opengl32.lib
					  )