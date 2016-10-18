cmake_minimum_required(VERSION 2.8)
 
PROJECT(Cone)

if(MSVC)
  set(VTK_DIR "D:/Develop/Source/VTK-7.0.0/build")
endif()
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
#add_executable(Cone MACOSX_BUNDLE vtk1.cpp)
add_executable(Cone  vtk1.cpp)

set_target_properties( Cone PROPERTIES CXX_STANDARD 14)


if(VTK_LIBRARIES)
  target_link_libraries(Cone ${VTK_LIBRARIES})
else()
  target_link_libraries(Cone vtkHybrid vtkWidgets)
endif()