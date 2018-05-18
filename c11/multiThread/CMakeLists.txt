add_executable(mt s1.cpp)
target_compile_features(mt PRIVATE cxx_auto_type)

add_executable(future future.cpp)
set_property(TARGET future  PROPERTY CXX_STANDARD 11)

add_executable(waitCondition waitCondition.cpp)
set_target_properties( waitCondition PROPERTIES CXX_STANDARD 11)

#shared mutex using boost thread library
find_package(Boost COMPONENTS thread system)
if(${Boost_FOUND})
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(sharedMutex sharedMutex.cpp)
    target_link_libraries(sharedMutex ${Boost_LIBRARIES})
    set_property(TARGET sharedMutex  PROPERTY CXX_STANDARD 14)
endif()


add_executable(SP_atomic SP_atomic.cpp)
set_target_properties( SP_atomic PROPERTIES CXX_STANDARD 11)

