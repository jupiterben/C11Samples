find_package(AGG)

add_executable(agg1 agg1.cpp)
include_directories(${AGG_INCLUDE_DIR} "/usr/local/include/agg2")
target_link_libraries(agg1 ${AGG_LIBRARIES})
