#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int chain_length = 5;

    for (int i = 0; i < chain_length; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            printf("Process %d: PID = %d, PPID = %d\n", i + 1, getpid(), getppid());

        } else {
            wait(NULL);
            break;
        }
    }

    return 0;
}