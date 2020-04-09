// gcc -o mcc mc_critical.c -fopenmp -std=gnu11

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <omp.h>

#define N 50000

int main() {

    srand(0);

    int circle_points = 0;
    int square_points = 0;

    // for measuring time
    double start;
    double end;
    start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp for schedule (guided)
        for (int i = 0; i < N; i++) {

            // Generate random point x.
            double x = (double) rand() / RAND_MAX;

            // Generate random point y.
            double y = (double) rand() / RAND_MAX;

            // Calculate distance from (x, y) to origin.
            double distance = x * x + y * y;

            // If d <= 1 (meaning the point is inside the circle), increment circle_points.
            if (distance <= 1) {
#pragma omp critical (circle) // Marking one critical zone for the circle points.
                circle_points++;
            }

            // Increment square_points (= total number of points).
#pragma omp critical (square) // Marking one critical zone for the square points.
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
