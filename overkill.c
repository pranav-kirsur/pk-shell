#include "overkill.h"
#include "countargs.h"
#include "linkedlist.h"
#include "shell.h"
#include <stdio.h>
#include <signal.h>

void overkill(char **args)
{
    if (countargs(args) != 1)
    {
        fprintf(stderr, "pksh: overkill takes no arguments\n");
        return;
    }

    struct jobNode *job = getHead();
    while (job != NULL)
    {
        int pid = job->pid;
        job = job->next;
        //kill process with given pid
        if (kill(pid, SIGKILL) == -1)
        {
            //error handling
            perror("pksh: overkill");
        }
        
    }
    return;
}