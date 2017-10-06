/**
 * Program to scale and project data into 2D and find a centroid
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

long q(long n) {
    if(n<3) {
        return 1;
    }
    long val1;
    long val2;

    #pragma omp parallel firstprivate(val1, val2)
    {
    #pragma omp task
    {
        val1 = q(n-1);
    }
    // #pragma omp task  //unnecessary creation of new thread I think
    // {
    val2 = q(n-2);
    // }
    #pragma omp taskwait
    }
    //end of parallel pragma

    return q(n-val1) + q(n-val2);
}

int main(int argc, char** argv) {
    long out;
    if(argc!=2) {
        printf("Usage: %s <integer>\nExiting...\n",argv[0]);
        return 0;
    }
    long n = strtol(argv[1],NULL,10);

    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    out = q(n);
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    long msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;

    // Print output
    printf("q(%d) = %d\n",n,out);
    printf("found in %dms\n",msec);

    return EXIT_SUCCESS;
}
