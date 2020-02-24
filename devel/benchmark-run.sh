#!/bin/bash

set -x

./benchmark.c.out > stats.c.txt

./benchmark.cpp.out > stats.cpp.txt

./benchmark.cpp.fcxxss.out > stats.cpp.fcxxss.txt

java -cp . Test > stats.java.txt

python benchmark.py > stats.py.txt

./benchmark.pyx.fcxxss.out > stats.pyx.fcxxss.txt

