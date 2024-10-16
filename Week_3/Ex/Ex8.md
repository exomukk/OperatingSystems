Before Typing the Command:
Starting the Shell:

When you open a terminal, the shell (e.g., bash, zsh) is started as a process by the terminal emulator.
The shell reads configuration files (like .bashrc or .bash_profile) to set up the environment, which includes defining environment variables, aliases, and functions.
Prompt Display:

After the shell is ready, it displays a command prompt, indicating that it is waiting for user input. The prompt may include information like the username, hostname, and current directory.
When You Type a Command (e.g., ls -l):
Command Input:

As you type the command, the terminal captures your keystrokes and displays them on the screen.
Command Execution (Upon Pressing Enter):

When you press Enter, the shell processes the command in the following steps:
Parsing:
The shell parses the input to identify the command (ls) and any arguments (e.g., -l).
It checks for syntax errors and ensures the command is valid.
Path Resolution:
The shell resolves the command name to find its location in the directories listed in the PATH environment variable.
It locates the executable file for ls.
Process Creation:
The shell invokes the fork() system call to create a new child process.
The kernel creates a new process control block (PCB) for the child process, duplicating attributes from the parent process (the shell).
Executable Loading:
The child process uses the exec() family of functions to replace its memory with the ls program.
The kernel loads the executable into memory, setting up the execution environment.
Argument Passing:
The arguments (like -l) are prepared and passed to the ls program, typically by setting up the argument stack.
Execution:
The kernel transfers control to the ls executable.
The ls program executes and interacts with the file system to retrieve directory contents and format the output according to the -l option.
Blocking Behavior:

Since the command is run in the foreground (without &), the shell waits for the ls command to complete before proceeding.
The shell is effectively "blocked," meaning it cannot accept new input until the ls process terminates.
Output Display:

The output of the ls -l command is sent to the standard output (stdout), which is usually the terminal.
The output appears on your screen, displaying detailed information about the files in the current directory.
Process Termination:

After executing, the ls command returns an exit status to the kernel, indicating whether it succeeded or failed.
The shell retrieves this exit status, updates its internal state, and may display any relevant messages.
Returning Control to the Shell:

Once the ls command has completed and its output has been displayed, the shell regains control.
The command prompt is re-displayed, indicating that the shell is ready to accept a new command.