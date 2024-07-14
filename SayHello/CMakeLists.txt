add_executable(SayHello "SayHello.cpp"   )

target_include_directories(SayHello PUBLIC
                          "${PROJECT_SOURCE_DIR}/Include"
						  )

target_link_directories(SayHello PRIVATE
						"${PROJECT_SOURCE_DIR}/Libs"
						)

target_link_libraries(SayHello PRIVATE 
					  glfw3.lib
					  glad.lib
					  opengl32.lib
					  )