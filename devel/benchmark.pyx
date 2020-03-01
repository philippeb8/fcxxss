'''*

    Fornux C++ Superset -- Benchmark.
    
 '''


include "local/libc/time.pxd"
include "local/libc/sys/resource.pxd"

import os
import resource
from libc.stdio cimport printf
from libc.stdlib cimport malloc, free
from local.libc.time cimport clock_gettime
from local.libc.sys.resource cimport getrusage

cdef struct list_node:
    list_node * p

cdef int test():
    # Proper cyclic memory leaks management:
    cdef list_node * p
    cdef long ru_maxrss
    cdef long t
    #cdef long delta
    cdef int i = 0
    cdef timespec before, after;
    clock_gettime(CLOCK_REALTIME, & before);

    while True:
        i += 1
        
        # cycle
        p = <list_node *> malloc(sizeof(list_node))
        p.p = <list_node *> malloc(sizeof(list_node))
        p.p.p = <list_node *> malloc(sizeof(list_node))
        p.p.p.p = p
        
        if (i) > 500000:
            break

    # stats
    clock_gettime(CLOCK_REALTIME, & after);

    delta = <long> (((after.tv_sec - before.tv_sec) + (after.tv_nsec - before.tv_nsec) / 1000000000.0) * 1000000000.0);
    
    ru_maxrss = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
    printf("Cython, %li, %f, %li\n", delta, (i * 1000000000.0 / <double> delta), ru_maxrss)
    
    return 0

test()
