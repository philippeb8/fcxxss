#!/bin/bash

export FCXXSS_CC="cl.sh"
export FCXXSS_DIR=$(dirname $0)/..
export PATH=$FCXXSS_DIR/bin:$PATH

fcxxss-cl.sh "$@"
