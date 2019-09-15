#include "exec_kjob.h"
#include "shell.h"
#include "linkedlist.h"
#include "countargs.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

//kills a job with given job number
void exec_kjob(char **args)
{
    if (countargs(args) != 3)
    {
        fprintf(stderr, "pksh: kjob: Invalid number of arguments\n");
        return;
    }

    char *end;
    int jobnum = strtol(args[1], &end, 0);
    //error handling for str to int
    if (*end != '\0')
    {
        fprintf(stderr, "pksh: kjob: Argument for job number should be an integer\n");
        return;
    }

    int signum = strtol(args[2], &end, 0);
    //error handling for str to int
    if (*end != '\0')
    {
        fprintf(stderr, "pksh: kjob: Argument for signal number should be an integer\n");
        return;
    }

    //pid of the process to be killed
    int pid = 0;

    // find pid with given jobnum
    struct jobNode *job = getHead();
    while (job != NULL)
    {
        if (job->jobnum == jobnum)
        {
            pid = job->pid;
            break;
        }
        job = job->next;
    }

    // if no pid found
    if (pid == 0)
    {
        fprintf(stderr, "pksh: kjob: No job with given job number\n");
        return;
    }

    //send signal with error handling
    if (kill(pid, signum) == -1)
    {
        perror("pksh: kjob:");
    }

    return;
}
