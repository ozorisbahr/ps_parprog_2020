// gcc -O3 -fopenmp ex1.c -o ex1
// export OMP_NUM_THREADS=4 / 2 / 1
// OMP_PLACES=cores / threads(4) / sockets

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int N = 100000000;
    int count = 0;

    double start;
    double end;
    start = omp_get_wtime();

    //                              close / spread
    #pragma omp parallel proc_bind(close)
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            #pragma omp atomic
                count++;
        }
    }
        end = omp_get_wtime();

        printf("Time: %f sec with N: %d\n", end - start, N);

    return 0;
}

/* Benchmark: (in seconds)
 * ----------------------------------
 * Threads | Master | Close | Spread
 *    4    |   3.3  |  3.7  |   3.7
 *    2    |   6.2  |  6.2  |   6.3
 *    1    |  12.1  | 12.1  |  12.1
 * ----------------------------------
 * If we change the Affinity we almost get the same speeds if doesnt
 * matter if it is Master, Close or Spread Affinity.
 * Only with different Thread numbers we see a speed difference.
 * */