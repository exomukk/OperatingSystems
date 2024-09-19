// execpl() function: https://stackoverflow.com/questions/21558937/i-do-not-understand-how-execlp-works-in-linux
// https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_lib_ref/e/execlp.html

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child process (PID: %d) is copying the directory.\n", getpid());

        execlp("cp", "cp", "-r", "OS", "OS1", NULL);

        perror("execlp failed");
        exit(EXIT_FAILURE);
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