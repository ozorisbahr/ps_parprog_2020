#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

extern double A[10];
void work(int *index) {

    double temp[10];
    static int count;
}

double A[10];

int main() {

    int index[10];
    #pragma omp parallel
    work(index);
    printf("%d\n", index[0]);

    return 0;
}

