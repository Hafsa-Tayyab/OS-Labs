/*
Name: Hafsa Tayyab
Reg no:  23-NTU-CS-1163
Task Title:  Task 1 – Thread Information Display
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>    

#define threads 5   
void* threadFunction(void* arg){
    int threadNum = *(int*)arg;
    pthread_t threadID = pthread_self();

    int sleepTime = (rand() % 3) + 1;

    printf("Thread %d started. Thread ID: %lu\n",threadNum,threadID);
    printf("Thread %d will sleep for %d second(s)...\n",threadNum,sleepTime);
    
    sleep(sleepTime);

    printf("Thread %d completed after %d second(s).\n\n",threadNum,sleepTime);

    pthread_exit(NULL);
}
int main(){
    pthread_t thread[threads];
    int threadNumbers[threads];
    srand(time(NULL));
    printf("Creating %d threads...\n\n", threads);

    for(int i=0; i<threads; i++){
        threadNumbers[i] = i + 1; 
        int status = pthread_create(&thread[i], NULL, threadFunction, &threadNumbers[i]);
        
        if(status != 0){
            fprintf(stderr, "Error: Unable to create thread %d\n", i + 1);
            exit(1);
        }
    }
    for (int i = 0; i < threads; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("\nAll threads have completed execution.\n");
    return 0;
}