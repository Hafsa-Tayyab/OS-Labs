#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t download_slots;

void* download_file(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&download_slots); 
    printf("Download %d: Started\n", id);
    
    sleep(rand() % 5 + 1);
    
    printf("Download %d: Finished\n", id);
    sem_post(&download_slots);
    
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[8];
    sem_init(&download_slots, 0, 3);

    for (int i = 0; i < 8; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL, download_file, id);
    }

    for (int i = 0; i < 8; i++) pthread_join(threads[i], NULL);
    sem_destroy(&download_slots);
    return 0;
}