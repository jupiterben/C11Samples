find_package(OpenGL REQUIRED)
#find_package(GLFW REQUIRED)

aux_source_directory(".." SourceFiles)

add_executable(GLS1  ${SourceFiles} )
target_include_directories(GLS1 PUBLIC  "../../3rd/glfw/include" "../../3rd/glm" )
target_compile_definitions(GLS1 PRIVATE GLEW_STATIC GLEW_MX)
target_link_libraries(GLS1 ${OPENGL_LIBRARIES} glew glfw)
set_target_properties(GLS1 PROPERTIES CXX_STANDARD 11)

