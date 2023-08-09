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
