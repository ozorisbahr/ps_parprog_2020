// gcc -O3 -fopenmp ex1.c -o ex1
// export OMP_NUM_THREADS=4 / 2 / 1

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int N = 200000;
    int count = 0;

    double start;
    double end;
    start = omp_get_wtime();

    //                              close / spread
    #pragma omp parallel for proc_bind(master)
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                for(int k = 0; k < N; k++) {
                    count++;
                }
            }
        }
        end = omp_get_wtime();

        printf("Time: %f sec with N: %d\n", end - start, N);

    return 0;
}

/* Benchmark: (in seconds)
 * ----------------------------------
 * Threads | Master | Close | Spread
 *    4    |   3.7  |  3.7  |   3.7
 *    2    |   6.2  |  6.2  |   6.3
 *    1    |  12.1  | 12.1  |  12.1
 * ----------------------------------
 * If we change the Affinity we almost get the same speeds if doesnt
 * matter if it is Master, Close or Spread Affinity.
 * Only with different Thread numbers we see a speed difference.
 * */