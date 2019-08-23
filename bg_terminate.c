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
    printf("\n Process with PID %d exited %s\n ", child_pid, exit_status);
    return;
}