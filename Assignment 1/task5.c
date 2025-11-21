/*
Name: Hafsa Tayyab
Reg no:  23-NTU-CS-1163
Task Title:  Task 5 – Thread Communication (Without Struct or Prototype)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int student_ids[3] = {101, 102, 103};
char names[3][50] = {"Ali", "Sara", "Bilal"};
float gpas[3] = {3.7, 3.2, 3.9};

void* studentThread(void* arg){
    int i = *((int*)arg);
    free(arg);

    printf("Student ID: %d\n", student_ids[i]);
    printf("Name: %s\n", names[i]);
    printf("GPA: %.2f\n", gpas[i]);

    int* res = malloc(sizeof(int));
    if(res == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        pthread_exit(NULL);
    }
    if(gpas[i] >= 3.5){
        printf("Status: Dean’s List\n\n");
        *res = 1;
    }else{
        printf("Status: Not on Dean’s List\n\n");
        *res = 0;
    }
    pthread_exit((void*)res);
}
int main() {
    pthread_t threads[3];
    int deanResults[3];
    int deanCount = 0;

    printf("=== Student Database System ===\n\n");

    for(int i=0; i<3; i++){
        int* index = malloc(sizeof(int));
        *index = i;
        int status = pthread_create(&threads[i], NULL, studentThread, (void*)index);
        if(status != 0){
            fprintf(stderr, "Error: Unable to create thread %d\n",i+1);
            exit(1);
        }
    }
    for(int i=0; i<3; i++){
        int* result;
        pthread_join(threads[i], (void**)&result);
        deanResults[i] = *result;

        if(deanResults[i] == 1)
            deanCount++;
            
        free(result);
    }

    printf("Main thread: %d student(s) made the Dean’s List.\n", deanCount);

    return 0;
}