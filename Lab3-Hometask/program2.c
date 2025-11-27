#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    if (pid == 0) {
        execlp("date", "date", NULL);
        perror("execlp failed");
    } else {
        wait(NULL);
        printf("Child finished\n");
    }
    return 0;
}
