find_package(Vulkan)

add_executable(device device.cpp util_init.cpp)
target_include_directories(device PUBLIC ${VULKAN_INCLUDE_DIR})
target_link_libraries(device ${VULKAN_LIBRARY})
