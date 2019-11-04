#!/bin/bash

export FCXXSS_CC="cl.sh"
export FCXXSS_DIR=$(dirname $0)/..
export PATH=$FCXXSS_DIR/bin:$PATH

bash -c "fcxxss-cl.sh $@"
