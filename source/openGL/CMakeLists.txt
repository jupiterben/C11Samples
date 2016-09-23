
add_library(glew glew.c)
target_include_directories(glew PUBLIC ".")
target_compile_definitions(glew PRIVATE GLEW_STATIC)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(test1  test1.cpp)
target_include_directories(test1 PUBLIC ".")
target_compile_definitions(test1 PRIVATE GLEW_STATIC)
target_link_libraries(test1 ${OPENGL_LIBRARIES} glew ${GLUT_LIBRARIES} )
