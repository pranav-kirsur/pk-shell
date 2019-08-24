#include <signal.h>
#include "bg_terminate.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "shell.h"
#include <string.h>

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
    char program_name[100] = "Process";
    for (int i = 0; i < 50; i++)
    {
        if (bg_proc_names[i].pid == child_pid)
        {
            strcpy(program_name, bg_proc_names[i].name);
        }
    }

    printf("\n \033[0;91m%s with PID %d exited %s\033[0m\n ", program_name, child_pid, exit_status);
    return;
}