'''*

    Fornux C++ Superset -- Benchmark.
    
 '''


import time
import os
import resource


class list_node:
    def __init__(self):
        p = 0



def test():
    # Proper cyclic memory leaks management:
    before = int(round(time.time() * 1000000000))
    
    i = 0
    while True:
        i += 1
        
        # cycle
        p = list_node()
        p.p = list_node()
        p.p.p = list_node()
        p.p.p.p = p
            
        if (i) > 500000:
            break

    # stats
    after = int(round(time.time() * 1000000000))
    
    ru_maxrss = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
    print("Python, %li, %f, %li" % ((after - before), i * 1000000000.0 / (after - before), ru_maxrss))

    return 0


test()
