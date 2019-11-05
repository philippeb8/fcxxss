#!/bin/bash
#
# Microsoft Visual Studio Compiler Wrapper
#
# Copyright (c) Fornux Inc. 2019
#

ROOTDIR=$(dirname "$0")/..

$ROOTDIR/bin/clang-cl.exe "$@"
