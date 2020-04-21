#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {


    #pragma omp parallel
    {
        printf("Hello World from Thread %d\n", omp_get_thread_num());
    }

    printf("%d Processor cores are available!\n", omp_get_num_procs());

    return 0;
}