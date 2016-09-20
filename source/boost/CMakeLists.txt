
find_package(Boost COMPONENTS filesystem )
if(${Boost_FOUND})    
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(fileSystem source/boost/fileSystem.cpp)
    target_link_libraries(fileSystem ${Boost_LIBRARIES})
endif()
