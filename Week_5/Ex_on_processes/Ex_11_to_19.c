#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

/* EXERCISE 11
8 times
*/

/* EXERCISE 12
(a) 5 processes are created
(b) PID: 3376, i = 0 
    PID: 3376, i = 1 
    PID: 3376, i = 2 
    PID: 3376, i = 3 
    PID: 3376, i = 4 
*/

/* EXERCISE 13
32 processes
*/
/* EXERCISE 14
int main(int argc, char *argv[]){
   pid_t pid1, pid2;
   int status1, status2;

   pid1 = fork();
   if (pid1 == 0){
      sleep(5);
      exit(5);
   }

   pid2 = fork();
   if (pid2 == 0){
      sleep(1);
      exit(1);
   }

   waitpid(pid1, &status1, 0); 
   waitpid(pid2, &status2, 0);
}
*/

/* EXERCISE 15
int main(){
   pid_t pid;
   pid = fork();
   if (pid == 0){
      int n;
      printf("Enter starting integer: \n");
      scanf("%d", &n);
      printf("%d ", n);
      while (n > 1){
         if (n % 2 == 0){
            n = n / 2;
         } else{
            n = 3*n + 1;
         }
         printf("%d ", n);
      }
   } else {
      wait(NULL);
   }
}
*/

/* EXERCISE 16: deo biet*/

/* EXERCISE 17: new - running - waiting - ready - terminated*/

/* EXERCISE 18
int main (int argc, char *argv[]) {
   pid_t childpid = 0;
   int i;
   for (i = 1; i < 5; i++){
      if ((childpid = fork()) <= 0){ 
         execl("/bin/date", "date", NULL);  
         perror("execl failed");
         exit(1);
      } else {
         fprintf(stderr, "i:%d process ID:%ld child ID:%ld, parent ID:%ld\n", i, (long)getpid(), (long)childpid,(long)getppid());
         wait(NULL);
      }
   }
   return 0;
}

4 child processes wil execute the "date" command
1 parent process will execute fprintf command since it's in the else block?
*/

/* EXERCISE 19: yes sir*/