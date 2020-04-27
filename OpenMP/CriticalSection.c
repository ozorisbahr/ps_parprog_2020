#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int N = 100;

    int a[N];
    int b[N];

    int ia = 0;
    int ib = 0;
    int itotal = 0;

    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = N - i;
    }


#pragma omp parallel
{
#pragma omp sections
 {
 #pragma omp section
  {
  for(int i = 0; i < N; i++) {
    ia = ia + a[i];
  }
  #pragma omp critical (c1)
   {
    itotal = itotal + ia;
   }}
  #pragma omp section
  {
  for(int i = 0; i < N; i++) {
    ib = ib + b[i];
  }
  #pragma omp critical (c1)
   {
    itotal = itotal + ib;
   }
  }
 }
}


    return 0;
}