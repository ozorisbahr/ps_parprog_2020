#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * Function to merge to sub-arrays (arr[left..mid] and arr[mid+1..right])
 * */
void merge(int arr[], int left, int mid, int right) {

    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    i = 0;      // Initial index of first subarray
    j = 0;      // Initial index of second subarray
    k = left;   // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Recursive and sequential merge sort algorithm.
 * */
void merge_sort_recursive(int32_t arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_recursive(arr, left, mid);
        merge_sort_recursive(arr, mid + 1, right);

        merge(arr, left, mid, right);
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

    // recursive call
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

    int32_t *arr;
    arr = (int32_t *) calloc(n, sizeof(int32_t));

    if (arr == NULL) {
        printf("MALLOC ERROR\n");
        return EXIT_FAILURE;
    }

    // fill array with pseudo random numbers
    srand(0);

    for (int i = 0; i < n; i++) {
        arr[i] = rand() / 10000000;
    }
    /******************************************************************************/


    // print array
    printf("Before: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    double start_time = omp_get_wtime();

    merge_sort_recursive(arr, 0, n - 1);

    double end_time = omp_get_wtime();


    printf("After: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    assert(is_array_sorted(arr, n));
    printf("time: %2.2f seconds\n", end_time - start_time);
    return EXIT_SUCCESS;
}


/** is_array_sorted algorithm copied from https://www.geeksforgeeks.org/program-check-array-sorted-not-iterative-recursive/ **/
/** merge_sort_recursive algorithm inspired by https://www.geeksforgeeks.org/merge-sort/ **/