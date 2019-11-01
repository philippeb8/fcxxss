/**

    Fornux C++ Superset -- Example.

    Outputs ('clang' on Linux):
    
    Speed: 73115.324984 loops / s; Memory usage: 3912 kilobytes
    
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
#include <sys/time.h>
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
    struct timeval before, after;
 
    gettimeofday(& before, (struct timezone *) NULL);
#endif
    
    for (int i = 0; ; ++ i)
    {
        // cycle
        struct list_node * p = malloc(sizeof(struct list_node));
        p->p = malloc(sizeof(struct list_node));
        p->p->p = malloc(sizeof(struct list_node));
        p->p->p->p = p;
        
        // stats
#if defined(_WIN32)
		time(& after);
		
        printf("\rSpeed: %f loops / s; Memory usage: %ld kilobytes", i * 1.0 / (after - before), GetMemoryUsage(GetCurrentProcessId()) / 1024);
        fflush(stdout);
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
        gettimeofday(& after, (struct timezone *) NULL);
		
        struct rusage r_usage;
        getrusage(RUSAGE_SELF, & r_usage);

        printf("\rSpeed: %f loops / s; Memory usage: %ld kilobytes", i * 1000000.0 / time_diff(before , after), r_usage.ru_maxrss);
        fflush(stdout);
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
