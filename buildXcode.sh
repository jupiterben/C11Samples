#!/bin/bash
mkdir build
cd build
cmake -G "Xcode" ..
cd ..
cmake --build build