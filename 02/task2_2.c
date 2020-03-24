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

    for (size_t j = 0; j < N; ++j) {
        for (size_t i = 0; i < N; ++i) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

    FILE * output;
    output = fopen("output2.txt", "w");

    for (size_t x = 0; x < N; x++)
    {
        for (size_t y = 0; y < N; y++)
            fprintf(output,"%d ", c[x][y]);
        fprintf(output,"\n");
    }

    fclose(output);

    return 0;
}