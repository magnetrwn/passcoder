#!/usr/bin/sh
set -e

if ! command -v astyle &>/dev/null; then
    echo "Please install \"astyle\" first!"
    exit 1
fi

astyle --mode=c \
       --lineend=linux \
       --suffix=none \
       --max-code-length=120 \
       --style=attach \
       --indent=spaces=4 \
       --indent-col1-comments \
       --pad-header \
       --unpad-paren \
       --pad-oper \
       --pad-comma \
       --pad-oper \
       --recursive \
       ./*.cpp,*.hpp,*.tpp

if ! command -v cppcheck &>/dev/null; then
    echo "Missing \"cppcheck\", skipping lint step."
    exit
fi

cppcheck --enable=style --std=c++14 include
cppcheck --enable=style --std=c++14 src
