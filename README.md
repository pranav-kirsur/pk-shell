# pksh
pksh is a basic shell that executes commands. It is written in C and uses C library as well as POSIX functions. It supports job control, piping, and redirection. It also supports running commands from history. Signal handling for Ctrl + C and Ctrl + Z is also present.

# Compiling the code
Run `make` in the directory containing the shell files.

# Executing the code
Run `./shell` in the directory where make was just run

# Cleaning up
Run `make clean`  in the directory. This will remove the object files and the `shell`  executable for the directory.

# Description of files in the code

Each header file contains function declarations along with a small description of what the function does.

Each C file contains a function that performs a specific objective.

Thus, modularity in the code is accomplished.

We now proceed to give an overview of the files:

1. `bg_terminate.c` : This contains the handler that runs when a background process exits
2. `exec_cd.c` : This executes the cd function of the shell.
3. `exec_echo.c` : This executes the echo function of the shell.
4. `exec_ls.c` : This executes the ls function of the shell.
5. `exec_pinfo.c` : This executes the pinfo function that prints process information.
6. `execute.c` : This contains the function that either calls a function associated with a builtin, or calls launch() to launch an external process.
7. `init.c` : Initialises the shell.
8. `launch.c` : Launches the external commands, both background and foreground.
9. `loop.c` : Contains the Read - Eval - Print loop
10. `main.c` : Contains main function that intitialises the shell and calls loop()
11. `Makefile` : Contains rules for compiling the code.
12. `parse.c` : Parses string according to given delimiter.
13. `prompt.c` : Prints prompt for the shell
14. `README.md` : Contains instructions for compiling and running the code. It also contains information about the files.
15. `history.c` : Contains history function that prints history
16. `nightswatch.c`: Contains nightswatch function
17. `shell.h` : Contains global variables used throughout many functions
18. `countargs.c` : Contains function that counts the number of arguments from a list
19. `exec_bg.c` : Contains function that runs a stopped background process
20. `exec_jobs.c` : Lists jobs that are in the background that were started from shell.
21. `exec_kjob.c` : Function for sending a signal to a job with given job number
22. `exec_setenv.c` : Sets an environment variable to a given value
23. `exec_unsetenv.c` : Unsets value of given environment variable
24. `execute_command.c` : Executes the given command, either builtin or external
25. `execute_pipeline.c` : Executes a piped series of commands
26. `linkedlist.c` : Contains the implementation of the linked list used for job control
27. `overkill.c` : Contains function that kills all background jobs
28. `quit.c` : Function to exit the shell
29. `recall_history.c` : Implements execution of commands from history when up arrow key is pressed
30. `sighandlers.c` : Contains signal handlers for Ctrl + Z and Ctrl + C
