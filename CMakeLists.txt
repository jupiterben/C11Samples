cmake_minimum_required(VERSION 3.6)

project(cppSamples)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${cppSamples_SOURCE_DIR}/cmake")

option(BUILD_C11 "Builds C11 Project" OFF)
option(BUILD_BOOST "Builds Boost Project" OFF)
option(BUILD_CUDA "Builds CUDA Project" OFF)
option(BUILD_INTELTBB "Builds TBB Project" OFF)
option(BUILD_OPENCL "Builds OPENCL Project" OFF)
option(BUILD_OPENMP "Builds OPENMP Project" OFF)
option(BUILD_VULKAN "Builds VULKAN Project" OFF)
option(BUILD_MULTITHREAD "Builds MULTITHREAD Project" ON)


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
find_package(TBB REQUIRED)
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
find_package(OpenGL REQUIRED)


##########vtk


##########MULTITHREAD
if(BUILD_MULTITHREAD)
    add_subdirectory(source/multiThread)
endif()

