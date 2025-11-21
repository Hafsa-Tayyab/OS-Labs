#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 4
int varg = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    int varl = 0;
    pthread_mutex_lock(&lock);
    varg++;
    pthread_mutex_unlock(&lock);
    varl++;
    int pid = getpid();
    printf("Thread %d executing: global=%d local=%d pid=%d\n",thread_id, varg, varl, pid);
    return NULL;
}
int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf("Main executing: global=%d pid=%d\n", varg, getpid());
    return 0;
}
