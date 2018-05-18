set CurrentDir=%cd%
set VendorDir=%~dp0../../Vendor
set DefaultProject=standard

::package dir
set CMAKE_ROOT=%VendorDir%/cmake-3.9.4-win64-x64
set QTDIR=%VendorDir%/QT/5.8/msvc2015_64
set VTKDIR=%VendorDir%/VTK-7.1.1/build
::bin
set path=%QTDIR%/bin;%CMAKE_ROOT%/bin;%path%
::qt options
set QT_QPA_PLATFORM_PLUGIN_PATH=%QTDIR%/plugins/platforms

::source dir
set BuildProject="%1"
if %BuildProject%=="" set BuildProject=%DefaultProject%
set SourceDir=%~dp0source/%BuildProject%

::change to build dir
mkdir %~dp0build
cd %~dp0build
mkdir %BuildProject%
cd %BuildProject%

::make
cmake -G "Visual Studio 14 2015 Win64" %SourceDir%
::build
cmake --build .

::back to 
cd %CurrentDir%