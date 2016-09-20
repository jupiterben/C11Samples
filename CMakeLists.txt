cmake_minimum_required(VERSION 3.6)

project(cppSamples)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${cppSamples_SOURCE_DIR}/cmake")

option(BUILD_C11 "Builds C11 Sample Project" OFF)
option(BUILD_BOOST "Builds Boost Sample Project" OFF)
option(BUILD_CUDA "Builds CUDA Sample Project" OFF)
option(BUILD_INTELTBB "Builds TBB Sample Project" ON)
option(BUILD_OPENCL "Builds OPENCL Sample Project" OFF)
option(BUILD_OPENMP "Builds OPENMP Sample Project" OFF)
option(BUILD_VULKAN "Builds VULKAN Sample Project" OFF)
option(BUILD_MULTITHREAD "Builds MULTITHREAD Sample Project" ON)
option(BUILD_VTK "Builds VTK Sample Project" OFF)


####### buid c11
if(BUILD_C11)
    add_subdirectory(source/c11)
endif()

#######  opencl
if(BUILD_OPENCL)
    add_subdirectory(source/openCL)
endif()

########  openMP
if(BUILD_OPENMP)
    add_subdirectory(source/openMP)
endif()

###########  tbb
if(BUILD_INTELTBB)
    add_subdirectory(source/inteltbb)
endif()

###########  vulkan
if(BUILD_VULKAN)
find_package(Vulkan REQUIRED)
endif()

###########  cuda
if(BUILD_CUDA)
find_package(CUDA REQUIRED)
endif()

#######boost
if(BUILD_BOOST)
     add_subdirectory(source/boost)
endif()


#########opengl
#find_package(OpenGL REQUIRED)


##########vtk
if(BUILD_VTK)
    add_subdirectory(source/vtk)
endif()

##########MULTITHREAD
if(BUILD_MULTITHREAD)
    add_subdirectory(source/multiThread)
endif()

