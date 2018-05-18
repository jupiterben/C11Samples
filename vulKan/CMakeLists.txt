
if (MSVC)
   set( ENV{VULKAN_SDK} "D:/Develop/SDK/vulkansdk/1.0.8.0" )
endif()

find_package(Vulkan)
if(${Vulkan_FOUND})
    add_executable(device device.cpp util_init.cpp)
    target_include_directories(device PUBLIC ${VULKAN_INCLUDE_DIR})
    target_link_libraries(device ${VULKAN_LIBRARY})
endif()