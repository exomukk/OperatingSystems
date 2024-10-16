A Thread Control Block (TCB) stores information necessary to manage a thread in an operating system. Here are its typical fields:

1. Thread ID: A unique identifier for the thread.

Purpose: To differentiate between multiple threads in a system.
2. Thread State: Indicates the current state of the thread (e.g., running, ready, waiting, terminated).

Purpose: To track the lifecycle of the thread.
3. Program Counter (PC): Stores the address of the next instruction to be executed by the thread.

Purpose: Allows the thread to resume execution from where it left off after being interrupted.
4. Registers: Stores the values of the CPU registers when the thread is switched out.

Purpose: To save the thread's execution context so it can be restored when the thread is resumed.
5. Stack Pointer: Points to the thread’s stack, which stores local variables, return addresses, and function call information.

Purpose: Keeps track of the thread's stack for function calls and local variables.
6. Thread Priority: Indicates the priority level of the thread.

Purpose: Helps the scheduler determine the order of thread execution.
7. Thread Local Storage (TLS): Memory for storing thread-specific data that is not shared with other threads.

Purpose: Allows each thread to maintain its own instance of certain data.
8. Scheduling Information: Includes details needed by the scheduler, such as how long the thread has been running or when it last ran.

Purpose: Helps in making scheduling decisions, like determining when the thread should be scheduled next.