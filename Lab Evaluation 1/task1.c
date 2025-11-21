/*
Name: Hafsa Tayyab
Reg no. :23-NTU-CS-1163
Lab Evaluation 1
--------------------------------------------------------------------------
Question:
Write a C program that creates 4 threads. Each thread should:
1. Receive a unique number N as an argument (use values: 10, 20, 30, 40)
2. Calculate the sum of numbers from 1 to N
3. Print the thread number and calculated sum
4. Return the sum through thread's return value
-> Main thread should:
1. Create all 4 threads and pass arguments Wait for all threads to complete
2. Collect all return values
3. Calculate and print the total of all sums
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* calSum(void* arg){
    int N=*(int*)arg;
    int* sum = malloc(sizeof(int));
    *sum = 0;

    for(int i=1; i<=N; i++){
        *sum += i;
    }
    printf("Thread for N=%d, Calculated Sum: %d \n", N, *sum);
    pthread_exit(sum);
}
int main(){
    pthread_t threads[4];
    int nums[4] = {10,20,30,40};
    int* result;
    int totalSum = 0;
    printf("\n");
    for(int i=0; i<4; i++){
        pthread_create(&threads[i], NULL, calSum, &nums[i]);
    }

    for(int i=0; i<4; i++){
        pthread_join(threads[i], (void**)&result);
        totalSum += *result;
        free(result);
    }

    printf("\nMain Thread: Total of all sums = %d\n\n",totalSum);
    return 0;
}

/*
Remarks:
In this program, multithreading is demonstrated using pthreads.
The program creates four threads using pthread_create.
Each thread computes the sum of numbers from 1 to N and returns it to the main thread.
The main thread then aggregates all results by using pthread_join and prints the total sum.
*/