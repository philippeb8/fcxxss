#!/bin/bash

export PATH=$FCXXSS_DIR/bin:$PATH
export FCXXSS_CC="cl.sh"
export FCXXSS_DIR=$(dirname $0)/..

bash -c "fcxxss-cl.sh $@"
