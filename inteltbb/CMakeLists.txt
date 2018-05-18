find_package(TBB REQUIRED)

add_executable(tbb tbb.cpp)
target_include_directories(tbb PUBLIC ${TBB_INCLUDE_DIR})
target_link_libraries(tbb ${TBB_LIBRARIES})

set_property(TARGET tbb  PROPERTY CXX_STANDARD 11)
