find_package(TBB REQUIRED)

add_executable(tbb tbb.cpp)
include_directories(${TBB_INCLUDE_DIR})
target_link_libraries(tbb ${TBB_LIBRARIES})

set_property(TARGET tbb  PROPERTY CXX_STANDARD 11)
