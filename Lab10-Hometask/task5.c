#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t stations;

void* wash_car(void* arg) {
    int id = *(int*)arg;
    printf("Car %d arriving at station...\n", id);
    
    sem_wait(&stations); 
    printf("Car %d is being washed.\n", id);
    
    sleep(3); 
    
    printf("Car %d wash finished. Leaving.\n", id);
    sem_post(&stations);
    return NULL;
}

int main() {
    pthread_t cars[5];
    int car_ids[5];
    sem_init(&stations, 0, 2); 

    for (int i = 0; i < 5; i++) {
        car_ids[i] = i + 1;
        pthread_create(&cars[i], NULL, wash_car, &car_ids[i]);
    }

    for (int i = 0; i < 5; i++) pthread_join(cars[i], NULL);
    return 0;
}