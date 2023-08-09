#!/usr/bin/sh
set -e

if ! command -v astyle &>/dev/null
then
    echo "Please install \"astyle\" first!"
    exit 1
fi

astyle --mode=c \
       --lineend=linux \
       --suffix=none \
       --max-code-length=112 \
       --style=attach \
       --break-return-type \
       --pad-header \
       --pad-oper \
       --pad-comma \
       --indent=spaces=4 \
       --squeeze-lines=2 \
       --squeeze-ws \
       --recursive \
       ./*.cpp,*.hpp,*.tpp

if ! command -v cppcheck &>/dev/null
then
    echo "Missing \"cppcheck\", skipping lint step."
    exit
fi

cppcheck --enable=style --inconclusive --std=c++14 include
cppcheck --enable=style --inconclusive --std=c++14 src
