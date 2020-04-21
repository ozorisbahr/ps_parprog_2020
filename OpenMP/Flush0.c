#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int a, flag;

int foo() {
    return 5;
}

int main() {

    a = foo();
    #pragma omp flush(a)

    flag = 1;
    #pragma omp flush(flag)

    return 0;
}