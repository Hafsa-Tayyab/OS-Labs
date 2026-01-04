#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define K 3 
sem_t computers;
pthread_mutex_t array_mutex;
int computer_usage[K] = {0};

void* student(void* arg) {
    int id = *(int*)arg;
    int comp_id = -1;

    sem_wait(&computers);
    
    pthread_mutex_lock(&array_mutex); 
    for(int i = 0; i < K; i++) {
        if(computer_usage[i] == 0) {
            computer_usage[i] = id;
            comp_id = i;
            printf("Student %d is using Computer %d\n", id, comp_id);
            break;
        }
    }
    pthread_mutex_unlock(&array_mutex);
    sleep(2);
    pthread_mutex_lock(&array_mutex);
    computer_usage[comp_id] = 0;
    printf("Student %d left Computer %d\n", id, comp_id);
    pthread_mutex_unlock(&array_mutex);
    sem_post(&computers);
    return NULL;
}

int main() {
    pthread_t students[6];
    int ids[6];
    sem_init(&computers, 0, K);
    pthread_mutex_init(&array_mutex, NULL);
    for (int i = 0; i < 6; i++) {
        ids[i] = i + 1;
        pthread_create(&students[i], NULL, student, &ids[i]);
    }
    for (int i = 0; i < 6; i++) pthread_join(students[i], NULL);
    return 0;
}