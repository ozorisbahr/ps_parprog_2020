#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int a[1000];

    #pragma omp parallel for schedule(dynamic, 4)
        for(int i = 0; i < 1000; i++)               //for schedule together !
            a[i] = omp_get_thread_num();

    return 0;
}