/**

    Fornux C++ Superset -- Benchmark.
    
 */


import java.util.*;


class list_node
{
    public list_node p;
}


class Test 
{
    public static void main(String[] args) 
    {
        // Proper cyclic memory leaks management:
        long before, after;
        before = System.nanoTime();

        int i = 0;
        for (; ; ++ i)
        {
            // cycle
            list_node p = new list_node();
            p.p = new list_node();
            p.p.p = new list_node();
            p.p.p.p = p;
            
            if (i > 500000)
                break;
        }
        
        // stats
        after = System.nanoTime();

        long ru_maxrss = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();

        System.out.printf("Java, %d, %f, %d\n", (after - before), i * 1000000000.0 / (after - before), ru_maxrss);
    }
}
