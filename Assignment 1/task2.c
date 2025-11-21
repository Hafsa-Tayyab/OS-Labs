/*
Name: Hafsa Tayyab
Reg no:  23-NTU-CS-1163
Task Title:  Task 2 – Personalized Greeting Thread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 

void* greetingThread(void* arg){
    char* userName = (char*)arg;
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", userName);

    pthread_exit(NULL);
}
int main(){
    pthread_t thread;  
    char name[50];       

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = '\0';
    printf("\nMain thread: Waiting for greeting...\n");
    int status = pthread_create(&thread, NULL, greetingThread, (void*)name);

    if(status != 0){
        fprintf(stderr, "Error: Unable to create thread.\n");
        exit(1);
    }

    pthread_join(thread, NULL);

    printf("Main thread: Greeting completed.\n");

    return 0;
}