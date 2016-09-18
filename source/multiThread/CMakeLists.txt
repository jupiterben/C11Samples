add_executable(mt s1.cpp)
target_compile_features(mt PRIVATE cxx_auto_type)


add_executable(callonce callonce.cpp)
target_compile_features(callonce PRIVATE cxx_auto_type)

#shared mutex using boost thread library
if (WIN32 AND MSVC)
    set(ENV{BOOST_ROOT} "D:/Develop/Source/boost_1_61_0") 
    set(ENV{BOOST_LIBRARYDIR} "D:/Develop/Source/boost_1_61_0/bin.v2/libs")
endif()
find_package(Boost REQUIRED COMPONENTS
thread
)
if(${Boost_FOUND})
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(sharedMutex sharedMutex.cpp)
    target_link_libraries(sharedMutex ${Boost_LIBRARIES})
    set_property(TARGET sharedMutex  PROPERTY CXX_STANDARD 11)
endif()