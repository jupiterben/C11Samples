cmake_minimum_required(VERSION 3.9)

PROJECT(Cone)

set(VTK_DIR $ENV{VTKDIR})

find_package(VTK)

include(${VTK_USE_FILE})
 
add_executable(Cone MACOSX_BUNDLE vtk2.cpp)

set_target_properties( Cone PROPERTIES CXX_STANDARD 14)


if(VTK_LIBRARIES)
  target_link_libraries(Cone ${VTK_LIBRARIES})
else()
  target_link_libraries(Cone vtkHybrid vtkWidgets)
endif()