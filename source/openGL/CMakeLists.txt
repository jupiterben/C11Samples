
add_library(glew glew.c)
target_include_directories(glew PUBLIC ".")
target_compile_definitions(glew PRIVATE GLEW_STATIC)

find_package(OpenGL REQUIRED)

find_package(SDL2)
find_package(SDL2_image)


add_executable(GLS1 GLS1.cpp)
target_include_directories(GLS1 PUBLIC "." ${SDL2_INCLUDES})
target_compile_definitions(GLS1 PRIVATE GLEW_STATIC)
target_link_libraries(GLS1 ${OPENGL_LIBRARIES} glew ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY})
set_property(TARGET GLS1  PROPERTY CXX_STANDARD 11)


add_executable(test1 test1.cpp)
target_include_directories(test1 PUBLIC "../../3rd/include")
target_link_libraries(test1 gtest)