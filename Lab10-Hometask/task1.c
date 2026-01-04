#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 3 // Number of rooms
sem_t rooms_sem;
int occupied_count = 0;
pthread_mutex_t count_mutex;

void* person(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&rooms_sem); // Request a room
    
    pthread_mutex_lock(&count_mutex);
    occupied_count++;
    printf("Person %d entered. Rooms occupied: %d\n", id, occupied_count);
    pthread_mutex_unlock(&count_mutex);

    sleep(rand() % 3 + 1); // Stay for 1-3 seconds

    pthread_mutex_lock(&count_mutex);
    occupied_count--;
    printf("Person %d left. Rooms occupied: %d\n", id, occupied_count);
    pthread_mutex_unlock(&count_mutex);

    sem_post(&rooms_sem); // Vacate room
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[10];
    sem_init(&rooms_sem, 0, N); // Initialized to N 
    pthread_mutex_init(&count_mutex, NULL);

    for (int i = 0; i < 10; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL, person, id);
    }

    for (int i = 0; i < 10; i++) pthread_join(threads[i], NULL);
    sem_destroy(&rooms_sem);
    return 0;
}