#include <stdlib.h>
#include <stdio.h>
#define N 3

int main() {

    int a[N][N] = { {1, 1, 1},
                    {2, 2, 2},
                    {3, 3, 3}};

    int b[N][N] = { {1, 1, 1},
                    {2, 2, 2},
                    {3, 3, 3}};
    int c[N][N];
    int d[N][N];

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
    for (size_t j = 0; j < N; ++j) {
        for (size_t i = 0; i < N; ++i) {
            d[i][j] = a[i][j] * b[i][j];
        }
    }

    printf("Result matrix 1 is: \n");
    for (size_t x = 0; x < N; x++)
    {
        for (size_t y = 0; y < N; y++)
            printf("%d ", c[x][y]);
        printf("\n");
    }

    printf("Result matrix 2 is: \n");
    for (size_t x = 0; x < N; x++)
    {
        for (size_t y = 0; y < N; y++)
            printf("%d ", d[x][y]);
        printf("\n");
    }

    return 0;
}