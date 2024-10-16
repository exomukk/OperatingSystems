Parent process has one sum variable, and its two threads share this sum.
Child process 1 has its own sum variable, shared between its two threads.
Child process 2 has its own sum variable, shared between its two threads.
Thus, there are 3 distinct sum variables, one per process.