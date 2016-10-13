
project(QTSamples)

if(APPLE)
    set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt5.6.0/5.6/clang_64)
elseif(MSVC)
    if(CMAKE_CL_64)
        set(CMAKE_PREFIX_PATH D:/Develop/SDK/QT/5.6.0/5.6/msvc2015_64)
    else()
        set(CMAKE_PREFIX_PATH D:/Develop/SDK/QT/5.6.0/5.6/msvc2015_64)
    endif()
endif()


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
# Tell CMake to create the helloworld executable
add_executable(qt5s1  mainwindow.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(qt5s1 Qt5::Widgets)