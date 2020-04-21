#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void P_Merge(int *C, int *A, int *B, int na, int nb) {
    if (na < nb) {
        P_Merge(C, B, A, nb, na);
    } else if (na==0) {
        return;
    } else {
        int ma = na/2;
        int mb = 0;//BinarySearch(A[ma], B, nb);
        C[ma+mb] = A[ma];
        #pragma omp task
            P_Merge(C, A, B, ma, mb);
        #pragma omp task
            P_Merge(C+ma+mb+1,A+ma+1,B+mb,na-ma-1,nb-mb);
        #pragma omp taskwait
    }
}
void P_MergeSort(int *B, int *A, int n) {
    if (n==1) {
        B[0] = A[0];
    } else {
        int C[n];
        #pragma omp task
            P_MergeSort(C,A,n/2);
        #pragma omp task
            P_MergeSort(C+n/2,A+n/2,n-n/2);
        #pragma omp taskwait
            P_Merge(B,C,C+n/2, n/2, n-n/2);
    }
}
int main() {

    return 0;
}