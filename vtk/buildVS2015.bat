set CurrentDir=%cd%
set VendorDir=%~dp0../../../Vendor
set SourceDir=%~dp0

::package dir
set CMAKE_ROOT=%VendorDir%/cmake-3.9.4-win64-x64
::set VTKDIR=E:\Source\Other\VTK-7.1.1\build
set VTKDIR=D:\Vendor\vtk\6.1-7.x64\vtk\build
set Qt5_DIR=%VendorDir%/QT/5.8/msvc2015_64

::bin
set path=%CMAKE_ROOT%/bin;%VTKDIR%/bin/Debug;%path%

::change to build dir
mkdir %~dp0build
cd %~dp0build


::make
cmake -G "Visual Studio 14 2015 Win64" %SourceDir%
::build

::start sln
start Cone.sln
::back to 
cd %CurrentDir%