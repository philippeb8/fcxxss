#!/bin/bash

export FCXXSS_CC="clang++"
export FCXXSS_DIR=$(dirname $0)/..
export FCXXSS_UNGUARDED=$FCXXSS_DIR/bin/unguarded.txt

export PATH=$FCXXSS_DIR/bin:$PATH

fcxxss.sh "$@"
