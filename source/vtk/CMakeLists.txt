find_package(VTK)

if(${VTK_FOUND})

add_executable(vtk1 vtk1.cpp)
target_include_directories(vtk1 PUBLIC ${VTK_USE_FILE})

if(VTK_LIBRARIES)
  target_link_libraries(vtk1 ${VTK_LIBRARIES})
else()
  target_link_libraries(vtk1 vtkHybrid vtkWidgets)
endif()

endif()