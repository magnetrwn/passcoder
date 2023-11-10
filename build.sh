#!/usr/bin/sh
set -e

cd build
[ -f passcoder ] && rm passcoder
cmake ..
make
rm ../passcoder_build*.zip 2> /dev/null
rm -r CMakeFiles cmake_install.cmake CMakeCache.txt Makefile 2> /dev/null
zip -r "passcoder_build$(date +%s).zip" .
mv passcoder_build*.zip ../
mv compile_commands.json ../
./passcoder
