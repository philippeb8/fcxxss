# https://en.wikipedia.org/wiki/C_date_and_time_functions

cdef extern from "<sys/resource.h>" nogil:
    enum: CLOCK_REALTIME

    cdef struct timeval:
        long tv_sec
        long tv_usec

    cdef struct rusage:
        timeval ru_utime
        timeval ru_stime
        long ru_maxrss
        long ru_ixrss
        long ru_idrss
        long ru_isrss
        long ru_minflt
        long ru_majflt
        long ru_nswap
        long ru_inblock
        long ru_oublock
        long ru_msgsnd
        long ru_msgrcv
        long ru_nsignals
        long ru_nvcsw
        long ru_nivcsw

    int getrusage(int who, rusage *usage)
