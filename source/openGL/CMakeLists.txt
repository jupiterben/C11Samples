
add_library(glew glew.c)
target_include_directories(glew PUBLIC ".")
target_compile_definitions(glew PRIVATE GLEW_STATIC)



#find_package(SDL2)
#find_package(SDL2_image)
find_package(OpenGL REQUIRED)

add_executable(GLS1 GLS1.cpp)
target_include_directories(GLS1 PUBLIC "../../3rd/glfw/incldue")
target_compile_definitions(GLS1 PRIVATE GLEW_STATIC)
target_link_libraries(GLS1 ${OPENGL_LIBRARIES} glew glfw)
set_target_properties(GLS1 PROPERTIES CXX_STANDARD 11)

