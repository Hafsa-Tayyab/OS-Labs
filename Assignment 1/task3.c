/*
Name: Hafsa Tayyab
Reg no:  23-NTU-CS-1163
Task Title:  Task 3 – Number Info Thread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* numberInfoThread(void* arg){
    int num = *(int*)arg; 
    int square = num * num;
    int cube = num * num * num;

    printf("\nThread: Number = %d\n", num);
    printf("Thread: Square = %d\n", square);
    printf("Thread: Cube   = %d\n\n", cube);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread;  
    int number;       

    printf("Enter an integer: ");
    scanf("%d", &number);

    int status = pthread_create(&thread, NULL, numberInfoThread, (void*)&number);
    if (status != 0) {
        fprintf(stderr, "Error: Unable to create thread.\n");
        exit(1);
    }

    pthread_join(thread, NULL);
    printf("Main thread: Work completed.\n");

    return 0;
}