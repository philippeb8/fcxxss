/**

    Fornux C++ Superset -- Benchmark.
    
 */


#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>
#include <time.h>
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>
#endif


struct list_node
{
    struct list_node * p;
};


#if defined(_WIN32)
SIZE_T GetMemoryUsage( DWORD processID );
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
double time_diff(struct timeval x , struct timeval y);
#endif

int main()
{
#if defined(_WIN32)
    time_t before, after;
 
    time(& before);
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    struct timespec before, after;
 
    clock_gettime(CLOCK_REALTIME, & before);
#endif
    
    for (int i = 0; ; ++ i)
    {
        // cycle
        struct list_node * p = new list_node;
        p->p = new list_node;
        p->p->p = new list_node;
        p->p->p->p = p;
        
        // stats
#if defined(_WIN32)
        time(& after);
        
        printf("\rSpeed: %f loops / s; Memory usage: %ld kilobytes", i * 1.0 / (after - before), GetMemoryUsage(GetCurrentProcessId()) / 1024);
        fflush(stdout);
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
        clock_gettime(CLOCK_REALTIME, & after);
        
        struct rusage r_usage;
        getrusage(RUSAGE_SELF, & r_usage);

        long delta = ((after.tv_sec - before.tv_sec) + (after.tv_nsec - before.tv_nsec) / 1000000000.0) * 1000000000.0;

        printf("C++, %li, %f, %li\n", delta, i * 1000000000.0 / delta, r_usage.ru_maxrss);
        
        if (i > 500000)
            break;
#endif
    }
 
    return 0;
}

#if defined(_WIN32)
SIZE_T GetMemoryUsage( DWORD processID )
{
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;

    hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
                             PROCESS_VM_READ,
                             FALSE, 
                             processID );
    if (NULL == hProcess)
        return 0;

    if ( GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)) )
        return pmc.WorkingSetSize;

    CloseHandle( hProcess );
}
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;
     
    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
     
    diff = (double)y_ms - (double)x_ms;
     
    return diff;
}
#endif
