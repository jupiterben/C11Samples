cmake_minimum_required(VERSION 3.6)

include(CMakeToolsHelpers OPTIONAL)

## all samples
project(cppSamples)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${cppSamples_SOURCE_DIR}/CMake")


option(BUILD_C11 "Builds C11 Sample Project" OFF)#1
option(BUILD_BOOST "Builds Boost Sample Project" OFF)#2
option(BUILD_CUDA "Builds CUDA Sample Project" OFF)#3
option(BUILD_INTELTBB "Builds TBB Sample Project" OFF)#4
option(BUILD_OPENCL "Builds OPENCL Sample Project" OFF)#5
option(BUILD_OPENMP "Builds OPENMP Sample Project" OFF)#6
option(BUILD_VULKAN "Builds VULKAN Sample Project" OFF)#7
option(BUILD_MULTITHREAD "Builds MULTITHREAD Sample Project" ON)#8
option(BUILD_VTK "Builds VTK Sample Project" OFF)#9
option(BUILD_AGG "Builds AGG Sample Project" OFF )#10
option(BUILD_CGAL "Builds CGAL Sample Project" OFF)#11
option(BUILD_OPENGL "Builds OPENGL Sample Project" OFF)#12
option(BUILD_GOOGLETEST "Builds google test Sample Project" ON)#12


####### buid c11  #1
if(BUILD_C11)
    add_subdirectory(source/c11)
endif()
#######boost #2
if(BUILD_BOOST)
     add_subdirectory(source/boost)
endif()
###########  cuda #3
if(BUILD_CUDA)
    add_subdirectory(source/cuda)
endif()
###########  tbb $4
if(BUILD_INTELTBB)
    add_subdirectory(source/inteltbb)
endif()
#######  opencl #5
if(BUILD_OPENCL)
    add_subdirectory(source/openCL)
endif()
########  openMP #6
if(BUILD_OPENMP)
    add_subdirectory(source/openMP)
endif()
###########  vulkan $7
if(BUILD_VULKAN)
    if (MSVC)
        set( ENV{VULKAN_SDK} "D:/Develop/SDK/vulkansdk/1.0.8.0" )
    endif()
    add_subdirectory(source/vulKan)
endif()
########## MULTITHREAD #8
if(BUILD_MULTITHREAD)
    add_subdirectory(source/multiThread)
endif()
##########  vtk  #9
if(BUILD_VTK)
    add_subdirectory(source/vtk)
endif()
#########  AGG  #10
if(BUILD_AGG)
    add_subdirectory(source/agg)
endif()
#########  CGAL  #11
if(BUILD_CGAL)
    add_subdirectory(source/cgal)
endif()
#########opengl   #12
if(BUILD_OPENGL)
    add_subdirectory(source/openGL)
endif()

#########opengl   #12
if(BUILD_GOOGLETEST)
    add_subdirectory(3rd/googletest)
    add_subdirectory(source/gtest)
endif()
