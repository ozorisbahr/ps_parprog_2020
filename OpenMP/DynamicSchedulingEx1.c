#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int i, a[1000];

    #pragma omp parallel
    {
     #pragma omp for schedule(dynamic, 4)
        for(int i = 0; i < 1000; i++)
            a[i] = omp_get_thread_num();

    #pragma omp for schedule(guided)
        for(int i = 0; i < 1000; i++)
            a[i] = omp_get_thread_num();
    }

    return 0;
}