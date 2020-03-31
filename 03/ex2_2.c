#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 30000

void fillMatrixWithRandomValues(int **matrix) {
    for (int columns = 0; columns < N; columns++) {
        for (int rows = 0; rows < N; rows++) {
            matrix[columns][rows] = (int) (rand() % 10) + 1;
        }
    }
}


int hadamard(int **a, int **b, int **c) {
    
    size_t i;
    size_t j;
    
    // Parallelizing the outermost loop
#pragma omp parallel shared(a, b, c) private(i, j)
    {
#pragma omp for schedule (dynamic)
        for (j = 0; j < N; ++j) {
            for (i = 0; i < N; ++i) {
                c[j][i] = a[j][i] * b[j][i];
            }
        }
    }
    return 0;
}

int main() {

    srand(time(0));

    int **a;
    a = (int **) malloc(N * sizeof(int *));

    if (a == NULL) {
        printf("MALLOC ERROR\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < N; i++) {
        a[i] = malloc(N * sizeof(int *));
        if (a[i] == NULL) {
            printf("MALLOC ERROR\n");
            return EXIT_FAILURE;
        }
    }

    int **b;
    b = malloc(N * sizeof(int *));
    if (b == NULL) {
        printf("MALLOC ERROR\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < N; i++) {
        b[i] = malloc(N * sizeof(int *));
        if (b[i] == NULL) {
            printf("MALLOC ERROR\n");
            return EXIT_FAILURE;
        }
    }

    int **c;
    c = malloc(N * sizeof(int *));
    if (c == NULL) {
        printf("MALLOC ERROR\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < N; i++) {
        c[i] = malloc(N * sizeof(int *));
        if (c[i] == NULL) {
            printf("MALLOC ERROR\n");
            return EXIT_FAILURE;
        }
    }

    fillMatrixWithRandomValues((int *) a);
    fillMatrixWithRandomValues((int *) b);

    // for measuring time
    double start;
    double end;
    start = omp_get_wtime();

    // Execute the Hadamard product implementation
    hadamard((int *) a, (int *) b, (int *) c);

    // stop measuring the execution time
    end = omp_get_wtime();
    printf("Work took %f seconds\n", end - start);

    printf("Matrix A: \n");
//
//    for (int x = 0; x < N; x++) {
//
//        for (int y = 0; y < N; y++) {
//            int z = a[x][y];
//            printf("%d ", a[x][y]);
//        }
//        printf("\n");
//    }

    free(a);

    printf("\n");

//    printf("Matrix B: \n");
//    for (size_t x = 0; x < N; x++) {
//        for (size_t y = 0; y < N; y++) {
//            printf("%d ", b[x][y]);
//        }
//        printf("\n");
//    }

    free(b);

    printf("\n");

//    printf("Matrix A * B = C: \n");
//    for (size_t x = 0; x < N; x++) {
//        for (size_t y = 0; y < N; y++) {
//            printf("%d ", c[x][y]);
//        }
//        printf("\n");
//    }

    free(c);
    printf("Work took %f seconds\n", end - start);
    return 0;
}
