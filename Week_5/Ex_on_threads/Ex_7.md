Threads within the same process do not share their stacks, but the stack itself is stored in memory and does not need to be explicitly saved or restored in the TCB during a context switch. This is because:

Thread context switches only need to save the CPU registers (like the instruction pointer, program counter, etc.) that the thread was using at the time of the switch. These registers include the stack pointer (which points to the current position on the stack for the thread).

When the thread is switched out, the current stack pointer is stored in the TCB along with other CPU state information. When the thread is scheduled to run again, the saved stack pointer is restored, allowing the thread to resume execution exactly where it left off.

The entire stack doesn’t need to be saved in the TCB because the stack memory remains in place and unmodified while the thread is not running. The stack pointer alone is sufficient to allow the thread to resume execution.

Thus, saving the stack pointer in the TCB is enough to ensure the thread can continue executing with its own stack once it is re-scheduled.