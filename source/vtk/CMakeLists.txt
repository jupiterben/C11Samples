PROJECT(Cone)

if(MSVC)
set(VTK_DIR "C:/Program Files/VTK/")
endif()

find_package(VTK)
include(${VTK_USE_FILE})
 
add_executable(Cone MACOSX_BUNDLE vtk1.cpp)
#add_executable(Cone  vtk1.cpp)

set_target_properties( Cone PROPERTIES CXX_STANDARD 14)


if(VTK_LIBRARIES)
  target_link_libraries(Cone ${VTK_LIBRARIES})
else()
  target_link_libraries(Cone vtkHybrid vtkWidgets)
endif()