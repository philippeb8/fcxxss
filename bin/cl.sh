#!/bin/bash
#
# Microsoft Visual Studio Compiler Wrapper
#
# Copyright (c) Fornux Inc. 2019
#

ROOTDIR=$(dirname "$0")/..

export CL_PATH=$(cygpath -awp '/cygdrive/c/Program Files/LLVM/bin/')                                                           

$ROOTDIR/bin/gcc2msvc.exe $@
