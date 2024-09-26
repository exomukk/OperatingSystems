#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pids[5];
    int num_children = 5;

    for (int i = 0; i < num_children; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork");
            exit(1);
        
        } else if (pids[i] == 0) {
            printf("Child %d: PID = %d and PPID = %d\n", i+1, getpid(), getppid());
            exit(0);

        }
    }

    for (int i = 0; i < num_children; i++) {
        wait(NULL);
    }

    return 0;
}