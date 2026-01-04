#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t worker_availability;

void* task_runner(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&worker_availability);
    printf("Task %d is being processed by a worker...\n", id);
    
    sleep(rand() % 2 + 1); 
    
    printf("Task %d completed.\n", id);
    sem_post(&worker_availability);
    return NULL;
}

int main() {
    pthread_t tasks[10]; 
    int task_ids[10];
    sem_init(&worker_availability, 0, 3); 

    for (int i = 0; i < 10; i++) {
        task_ids[i] = i + 1;
        pthread_create(&tasks[i], NULL, task_runner, &task_ids[i]);
    }

    for (int i = 0; i < 10; i++) pthread_join(tasks[i], NULL);
    return 0;
}