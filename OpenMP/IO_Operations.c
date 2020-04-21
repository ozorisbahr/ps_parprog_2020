#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int i = 0, N = 1000;

 #pragma omp parallel sections
 {
    #pragma omp section {
        for (i = 0; i < N; i++) {
            (void) read_input(i);               // input thread
            (void) signal_read(i);
        }
    }

    #pragma omp section {
        for (i = 0; i < N; i++) {
            (void) wait_read(i);                // processing thread
            (void) process_data(i);
            (void) signal_processed(i);
        }
    }

    #pragma omp section {
        for (i = 0; i < N; i++) {
            (void) wait_processed(i);           // output thread
            (void) write_output(i);
        }
    }

 }
    return 0;
}