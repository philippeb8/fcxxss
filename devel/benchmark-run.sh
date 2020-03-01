#!/bin/bash

set -x

./benchmark.c.out

./benchmark.cpp.out

./benchmark.cpp.fcxxss.out

java -cp . Test

python benchmark.py

./benchmark.pyx.fcxxss.out

