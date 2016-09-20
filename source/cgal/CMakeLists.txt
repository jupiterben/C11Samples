find_package(CGAL)

add_executable(cgal1 cgal1.cpp)
include_directories(${CGAL_INCLUDE_DIR})
target_link_libraries(cgal1 ${CGAL_LIBRARIES})
