find_package(CUDA)

add_executable(cuda cuda.cpp)
target_include_directories(cuda PUBLIC ${CUDA_INCLUDES})
target_link_libraries(cuda ${CUDA_LIBRARIES})