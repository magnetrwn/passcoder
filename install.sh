#!/usr/bin/sh

cd build
rm passcoder
cmake ..
make
rm -r CMakeFiles cmake_install.cmake CMakeCache.txt Makefile
printf '\n\u001B[36mDone: Run "./passcoder" from inside the build folder.\u001B[0m\n'
# TODO: does not install to system yet.