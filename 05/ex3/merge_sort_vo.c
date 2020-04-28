#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
Problem description:
 The array is split into sub-arrays until each sub-array only holds one element. This way, all sub-arrays are sorted (since they only have 1 element).
 Then, all sub-array are merged with their "neighbouring" sub-array, and so on, until all are merged to one array.

 Therefore, when starting the merge operation we have a very large number of very small arrays.
 Merging them requires very little CPU time. That's why it makes sense to merge them sequentially up to a certain array length,
 in order to avoid the overheads of parallelism. Once the arrays have reached this certain size, the operation takes much more time
 and it becomes reasonable to parallelize it.
 */

// A binary search based function to find the position
// where item should be inserted in a[low..high]
int binary_search(int a[], int item, int low, int high) {
    if (high <= low)
        return (item > a[low]) ? (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == a[mid])
        return mid + 1;

    if (item > a[mid])
        return binary_search(a, item, mid + 1, high);
    return binary_search(a, item, low, mid - 1);
}

/**
 * Function to merge to arrays
 * */
void merge(int32_t c[], int32_t a[], int32_t b[], int32_t na, int32_t nb) {

    if (na < nb) {
        merge(c, b, a, nb, na);
    } else if (na == 0) {
        return;
    } else {
        size_t size_b = sizeof(b) / sizeof(b[0]);
        int32_t ma = na / 2;
        int32_t mb = binary_search(b, a[ma], nb - size_b, nb);
        printf("%d ", mb);
        c[ma + mb] = a[ma];
#pragma omp task
        merge(c, a, b, ma, mb);
#pragma omp task
        merge(c + ma + mb + 1, a + ma + 1, b + mb, na - ma - 1, nb - mb);
#pragma omp taskwait
    }
}

/**
 * Recursive and sequential merge sort algorithm.
 * */
void merge_sort_recursive(int32_t b[], int32_t a[], int n) {

    if (n == 1) {
        b[0] = a[0];
    } else {
        int32_t *c;
        c = (int32_t *) calloc(n, sizeof(int32_t));


#pragma omp task
        merge_sort_recursive(c, a, n / 2);

#pragma omp task
        merge_sort_recursive(c + n / 2, a + n / 2, n - n / 2);

#pragma omp taskwait
        merge(b, c, c + n / 2, n / 2, n - n / 2);
        free(c);
    }
}

/**
 * Function for checking whether or not an array's elements are ordered.
 * */
int is_array_sorted(int arr[], int n) {
    if (n == 1 || n == 0)
        return 1;

    // Unsorted pair found (Equal values allowed)
    if (arr[n - 1] < arr[n - 2]) {
        return 0;
    }

    // recurive call
    return is_array_sorted(arr, n - 1);
}

/**
 * Main function.
 * */
int main(int argc, char **argv) {

    /****************** handle input - copied from week04 - ex2 ******************/
    if (argc != 2) {
        fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    char *str = argv[1];
    char *endptr;
    long n = strtol(str, &endptr, 0);
    if (errno != 0) {
        perror("strtol");
        return EXIT_FAILURE;
    }
    if (endptr == str) {
        fprintf(stderr, "Error: no digits were found!\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Error: matrix size must not be negative!\n");
        return EXIT_FAILURE;
    }
    /******************************************************************************/

    /******** allocation of the array and filling it with random numbers **********/

    int32_t *a;
    a = (int32_t *) calloc(n, sizeof(int32_t));

    int32_t *b;
    b = (int32_t *) calloc(n, sizeof(int32_t));

    if (a == NULL || b == NULL) {
        printf("MALLOC ERROR\n");
        return EXIT_FAILURE;
    }

    // fill array with pseudo random numbers
    srand(0);

    double start_time;
    double end_time;

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < n; i++) {
            a[i] = rand() / 10000000;
        }
        /******************************************************************************/

    }
    // print array
    printf("Before: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    start_time = omp_get_wtime();


    merge_sort_recursive(b, a, n);


    end_time = omp_get_wtime();

    printf("After: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    assert(is_array_sorted(b, n));

    printf("time: %2.2f seconds\n", end_time - start_time);
    return
            EXIT_SUCCESS;
}


/** ARRAY SORTED OR NOT ALGORITHM FROM https://www.geeksforgeeks.org/program-check-array-sorted-not-iterative-recursive/ **/

