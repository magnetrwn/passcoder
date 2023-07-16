#!/usr/bin/sh
set -e

cd build
[ -f passcoder ] && rm passcoder
cmake ..
make
rm -r CMakeFiles cmake_install.cmake CMakeCache.txt Makefile 2> /dev/null
#zip -r "passcoder_build$(date +%s).zip" .
#mv passcoder_build* ../


# Run this from project root, it will generate a build zip for you!
# TODO: does not install to system yet.
