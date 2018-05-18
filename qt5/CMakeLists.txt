
project(QTSamples)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")


# Tell CMake to create the helloworld executable
set(theTarget qt5s1)
add_executable(${theTarget}  mainwindow.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(${theTarget} Qt5::Widgets)