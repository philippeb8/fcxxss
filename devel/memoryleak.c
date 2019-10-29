/**

    Fornux C++ Superset -- Example.

    Outputs:
    
    Speed: 73115.324984 loops / s; Memory usage: 3912 kilobytes
    
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


double time_diff(struct timeval x , struct timeval y);

struct list_node
{
    struct list_node * p;
};


int main()
{
    struct timeval before, after;
 
    gettimeofday(& before, (struct timezone *) NULL);
    
    for (int i = 0; ; ++ i)
    {
        // cycle
        struct list_node * p = malloc(sizeof(struct list_node));
        p->p = malloc(sizeof(struct list_node));
        p->p->p = malloc(sizeof(struct list_node));
        p->p->p->p = p;
        
        // stats
        gettimeofday(& after, (struct timezone *) NULL);
        struct rusage r_usage;
        getrusage(RUSAGE_SELF, & r_usage);
        printf("\rSpeed: %f loops / s; Memory usage: %ld kilobytes", i * 1000000.0 / time_diff(before , after), r_usage.ru_maxrss);
        fflush(stdout);
        //usleep(1);
    }
 
    return 0;
}

double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;
     
    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
     
    diff = (double)y_ms - (double)x_ms;
     
    return diff;
}
