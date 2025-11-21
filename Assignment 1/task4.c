/*
Name: Hafsa Tayyab
Reg no:  23-NTU-CS-1163
Task Title:  Task 4 – Thread Return Values (Factorial Calculation)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* factorialThread(void* arg);

int main(){
    pthread_t thread;   
    int number;         
    void* result;       
    
    printf("Enter a number: ");
    scanf("%d", &number);

    int status = pthread_create(&thread, NULL, factorialThread, (void*)&number);
    if(status != 0){
        fprintf(stderr, "Error: Unable to create thread.\n");
        exit(1);
    }

    pthread_join(thread, &result);
    long long* factorialResult = (long long*)result;
    printf("Main thread: Factorial result received = %lld\n",*factorialResult);

    free(factorialResult);

    return 0;
}

void* factorialThread(void* arg){
    int num = *(int*)arg;  
    long long* factorial = malloc(sizeof(long long));  

    if(factorial == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        pthread_exit(NULL);
    }

    *factorial = 1;  
    printf("Thread: Calculating factorial of %d...\n",num);

    for(int i = 1; i <= num; i++){
        *factorial *= i;
    }

    printf("Thread: Factorial of %d = %lld\n",num,*factorial);

    pthread_exit((void*)factorial);
}