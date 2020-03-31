#include <pthread.h>
#include <stdio.h>

void* thrfunc(void* arg) {
    printf("Hello from Thread %d\n", *(int*)arg);
}

int main(int *argc, char *argv[] ) {
    pthread_t thread[8];
    pthread_attr_t attr;
    int arg[8] = {0,1,2,3,4,5,6,7}; // has to be same size!
    int i;

    // setup joinable threads with system scope
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    // create N threads
    for(i = 0; i < 8; i++) {
        pthread_create(&thread[i], &attr, thrfunc, (void *) &arg[i]);
        // wait for N threads to finsih
    } for(i = 0; i < 8; i++) {
        pthread_join(thread[i],NULL);
    }

    return 0;
}