//Compile: gcc -fopenmp omp_hello.c -o hello
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, tid;

/* Fork a team of threads giving them their own copies of variables */
//pragma -> pragmatic information
//pragma -> way to communicate the information to the compiler
#pragma omp parallel private(nthreads, tid)
//#pragma omp parallel num_threads(8)private(tid) //num_threads --> clause to request threads
  {
	//each thread executes a copy of the code withing the structured block
  /* Obtain thread number */
  tid = omp_get_thread_num();
  printf("Hello World from thread %d\n", tid);

  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  }  /* All threads join master thread and disband */

}

//most compiler will create 1 thread for each core. 
//hyper-threading --> N*cores (N is the number of hardware threads per core)
//the order of output is random
//it is piped through the sort utility

//if you run it several times: 
//Typically, dynamic scheduling is not deterministic.
//everytime you run the program, different threads can run different chunks of work.
//it is even possible that a thread might not do any work because another thread is
//quicker and takes more work. 
//In fact, it might be possible forone thread to do all of the work.

//when we change the dynamic scheduling to static scheduling
//the allocation of work is deterministic and should not change
//between runs, and every thread gets work to do.

