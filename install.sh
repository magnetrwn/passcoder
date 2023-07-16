#!/usr/bin/sh

cd build
cmake ..
make
echo 'Done: Run "./passcoder" from inside the build folder.'