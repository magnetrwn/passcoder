#!/usr/bin/sh
set -e

cd build
[ -f passcoder ] && rm passcoder
cmake ..
make
rm -r CMakeFiles cmake_install.cmake CMakeCache.txt Makefile 2> /dev/null
printf '\n\u001B[36mDone: Run "./passcoder" from inside the build folder.\u001B[0m\n'
# TODO: does not install to system yet.