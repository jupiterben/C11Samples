add_library(glew glew.c)
target_include_directories(glew PUBLIC ".")
target_compile_definitions(glew PRIVATE GLEW_STATIC)


