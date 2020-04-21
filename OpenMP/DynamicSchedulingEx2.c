#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int i, j, a[1000][1000];

    #pragma omp parallel
    {
    #pragma omp for schedule(dynamic, 4)
        for (int i = 0; i < 1000; i++)
            for (j = 0; j < 1000; j++)
                a[i][j] = omp_get_thread_num();
    }

    return 0;
}