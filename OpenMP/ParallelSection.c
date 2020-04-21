#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int i, a[1000], b[1000];

    #pragma omp parallel private(i)
    {
    #pragma omp sections
     {
     #pragma omp section
         for(i = 0; i < 1000; i++)
             a[i] = 100;

     #pragma omp section
         for(i = 0; i < 1000; i++)
             b[i] = 200;
     }
    }

    return 0;
}