#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t bridge_capacity;
pthread_mutex_t print_mutex;

void* cross_bridge(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&bridge_capacity); 
    
    pthread_mutex_lock(&print_mutex); 
    printf("Car %d is crossing the bridge.\n", id);
    pthread_mutex_unlock(&print_mutex);

    sleep(rand() % 3 + 1); 

    pthread_mutex_lock(&print_mutex);
    printf("Car %d has crossed.\n", id);
    pthread_mutex_unlock(&print_mutex);
    
    sem_post(&bridge_capacity);
    return NULL;
}

int main() {
    pthread_t cars[8];
    int ids[8];
    sem_init(&bridge_capacity, 0, 3);
    pthread_mutex_init(&print_mutex, NULL);

    for (int i = 0; i < 8; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, cross_bridge, &ids[i]);
    }

    for (int i = 0; i < 8; i++) pthread_join(cars[i], NULL);
    return 0;
}