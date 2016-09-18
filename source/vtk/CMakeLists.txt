find_package(VTK REQUIRED)

include(${VTK_USE_FILE})
 
add_executable(vtk1 vtk1.cpp)
 
if(VTK_LIBRARIES)
  target_link_libraries(vtk1 ${VTK_LIBRARIES})
else()
  target_link_libraries(vtk1 vtkHybrid vtkWidgets)
endif()