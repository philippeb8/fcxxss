#!/bin/bash

set -x

export CYTHON_HOME=/home/philippeb8/devel/github/cython
export FCXXSS_HOME=/opt/fornux/cxx_superset

clang -O2 benchmark.c -o benchmark.c.out

clang++ -O2 benchmark.cpp -o benchmark.cpp.out

$FCXXSS_HOME/bin/fcxxss.sh -O2 benchmark.cpp -o benchmark.cpp.fcxxss.out

javac benchmark.javac

$CYTHON_HOME/bin/cython benchmark.py --embed --cplus -o benchmark.py.cpp
clang++ -O2 benchmark.py.cpp -isystem /usr/include/python2.7 -isystem $CYTHON_HOME/include/system -include Python.h -L /usr/lib/x86_64-linux-gnu -lpython2.7 -DCYTHON_UNUSED= -o benchmark.py.out

$CYTHON_HOME/bin/cython benchmark.pyx --embed --cplus -o benchmark.pyx.cpp
$FCXXSS_HOME/bin/fcxxss.sh -O2 benchmark.pyx.cpp -isystem /usr/include/python2.7 -isystem $CYTHON_HOME/include/system -include Cython.h -L /usr/lib/x86_64-linux-gnu -lpython2.7 -DCYTHON_UNUSED= -o benchmark.pyx.fcxxss.out
