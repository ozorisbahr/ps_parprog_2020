#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void pooh(int ID, double *index){}

int main() {

    double A[1000];

    #pragma omp parallel num_threads(4)
    {
        int ID = omp_get_thread_num();
        pooh(ID, A);
    }
    printf("all done\n");

    return 0;
}