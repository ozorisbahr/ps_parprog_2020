#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int a, b, flag;

int main() {

    #pragma omp flush(flag)
    while(!flag) {
    #pragma omp flush(flag)
    }

    #pragma omp flush(a)
    b = a;

    return 0;
}