add_library(AiCore "src/AiCore.cpp")

target_link_libraries(AiCore PRIVATE 
					  glfw
					  glad
					  opengl32.lib
					  )