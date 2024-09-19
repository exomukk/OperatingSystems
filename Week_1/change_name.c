#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char old_name[] = "OperatingSystem";
    char new_name[] = "OS";
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child process (PID: %d) is renaming the directory.\n", getpid());
        if (rename(old_name, new_name) == 0) {
                printf("Directory '%s' remaned to '%s'.\n", old_name, new_name);
            } else {
                perror("Error in renaming");
                exit(EXIT_FAILURE);
            }
    } else {
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not terminate successfully\n");
        }
    }

    return 0;
}