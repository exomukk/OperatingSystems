#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*the child will be come an orphan*/
int main() {
    pid_t child_pid = fork();
    if (child_pid > 0) {
        printf("parent. finish exec in 5s be for child %ld\n", (long) getpid());
        sleep(5);

    } else if (child_pid == 0) {
        printf("child. sleep 15s before exit %ld\n", (long) getpid());
        sleep(15);
        printf("child exit\n");
    }
    return 0;
}