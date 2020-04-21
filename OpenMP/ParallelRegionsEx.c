#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void pooh(int ID, double *index){}

int main() {

    int iam, nthreads;

    #pragma omp parallel private(iam, nthreads)
    {
        iam = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        printf("ThreadID %d, out of %d threads\n", iam, nthreads);

        if(iam == 0) { // ! Different control flow
            printf("Here is the Master Thread.\n");
        }
        else {
          printf("Here is another Thread.\n");
        }
    }

    return 0;
}