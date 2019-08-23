#include <signal.h>
#include "bg_terminate.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void bg_terminate(int signum)
{
    int status;
    int child_pid = waitpid(-1, &status, WNOHANG);
    if (child_pid == 0 || child_pid == -1)
    {
        // no bg_child has terminated
        return;
    }
    char *exit_status = (WIFEXITED(status)) ? "normally" : "abnormally";
    printf("\n \033[0;91mProcess with PID %d exited %s\033[0m\n ", child_pid, exit_status);
    return;
}