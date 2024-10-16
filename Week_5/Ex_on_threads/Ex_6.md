The Thread Control Block (TCB) contains entries for saving the content of the runtime registers but not for dynamically allocated variables (i.e., variables stored on the heap). Here’s why:

Run-time registers: These contain critical state information for the thread, such as the program counter, registers, and stack pointer. The TCB stores these because they must be restored when a thread is rescheduled to run.

Dynamically allocated variables: These are stored on the heap and are shared across all threads within the same process. The heap memory is not part of a thread's individual context (it's part of the process context). Therefore, there is no need to save this information in the TCB. The thread only needs to maintain its stack (for function calls and local variables), while dynamically allocated memory remains accessible as long as the process is running.

In summary, the TCB focuses on saving the thread-specific execution context, while heap memory is managed by the process and accessible to all threads within that process.