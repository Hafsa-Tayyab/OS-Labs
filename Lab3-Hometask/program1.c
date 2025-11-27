#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    pid_t pid = fork();

    if(pid < 0){
        perror("fork failed");
        return 1;
    }
    if(pid == 0){
        execlp("top", "top", NULL);
        perror("execlp failed");
    }else{
        printf("Child running 'top' with PID: %d\n", pid);
        wait(NULL);
        printf("Child process terminated.\n");
    }
    return 0;
}