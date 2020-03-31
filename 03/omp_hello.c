//Compile: gcc -fopenmp omp_hello.c -o hello
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int nthreads, tid;

	//#pragma omp parallel private(nthreads, tid)
	/* Fork a team of threads giving them their own copies of variables */
	#pragma omp parallel num_threads(4)private(tid) { //num_threads --> clause to request threads
		//each thread executes a copy of the code withing the structured block
		/* Obtain thread number 
		tid = omp_get_thread_num();
		printf("Hello World from thread %d\n", tid);

		/* Only master thread does this */
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
	}  // All threads join master thread and disband
}
