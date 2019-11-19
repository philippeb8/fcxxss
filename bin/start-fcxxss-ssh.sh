#!/bin/bash

export FCXXSS_CC="clang++"
export FCXXSS_DIR=$(dirname $0)/..

export PATH=$FCXXSS_DIR/bin:$PATH

fcxxss-ssh.sh "$@"
