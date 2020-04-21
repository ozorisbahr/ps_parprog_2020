// gcc -o mca mc_atomic.c -fopenmp -std=gnu11

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <omp.h>

#define N 500000000

int main() {

    int circle_points = 0;
    int square_points = 0;

    // for measuring time
    double start;
    double end;
    start = omp_get_wtime();

#pragma omp parallel
    {
        unsigned int my_seed = omp_get_thread_num();

#pragma omp for shared(circle_points, square_points)
        for (int i = 0; i < N; i++) {

            // Generate random point x.
            double x = (double) rand_r(&my_seed) / RAND_MAX;

            // Generate random point y.
            double y = (double) rand_r(&my_seed) / RAND_MAX;

            // Calculate distance from (x, y) to origin.
            double distance = x * x + y * y;

            // If d <= 1 (meaning the point is inside the circle), increment circle_points.
            if (distance <= 1) {
#pragma omp atomic
                circle_points++;
            }

            // Increment square_points (= total number of points).
#pragma omp atomic
            square_points++;
        }
    }

    // Calculate pi.
    double pi = (double) (4 * circle_points) / square_points;

    printf("Circle: %d, Square: %d\n", circle_points, square_points);

    // stop measuring the execution time
    end = omp_get_wtime();
    printf("Work took %f seconds\n", end - start);

    printf("Pi = %f\n", pi);

    // Terminate.
    return EXIT_SUCCESS;

}
