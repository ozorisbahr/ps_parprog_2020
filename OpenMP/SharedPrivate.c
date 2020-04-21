#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    #pragma omp parallel default(shared)
    {
        printf("Hello World\n");
    }

    int i = 1; // Dont code like this!!
    int j = 2;

    #pragma omp parallel private(i) \
    private(j)                          // two lines #pragma directive if needed
    {
        i = 8;
        j = 9;

        printf("i: %d, j: %d\n", i, j); // i: 8, j: 9 or i: 1, j: 2 !!
    }

    int k = 77;
    #pragma omp parallel shared(k)
    {
        k = omp_get_thread_num();
    }
    printf("Value of k = %d\n", k); // Value if k of the Last thread will be printed!

    return 0;

}