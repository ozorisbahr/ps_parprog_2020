#include <omp.h>
#include <stdio.h>

int main() {
    int data, flag = 0;
#pragma omp parallel num_threads(2) //man erstellt zwei threads
    {
        if (omp_get_thread_num()==0) { // 0-> master; man überprüft ob thread_id gleich 0 ist
            /* Write to the data buffer that will be read by thread */
            data = 42;
            /* Set flag to release thread 1 */
            flag = 1;
        }
        else if (omp_get_thread_num()==1) { //thread id wird geprüft, ob es gleich 1 ist
            /* Loop until we see the update to the flag */
            while (flag < 1) { //man wartet bis der flag auf 1 gesetzt ist
            }
            /* print flag and data */
            printf("flag=%d data=%d\n", flag, data);
        }
    }
    return 0;
}
