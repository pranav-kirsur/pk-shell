#include "exec_bg.h"
#include "linkedlist.h"
#include "shell.h"
#include "countargs.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void exec_bg(char **args)
{
    if (countargs(args) != 2)
    {
        fprintf(stderr, "pksh: bg takes only one argument: the job number\n");
        return;
    }

    char *end;
    int jobnum = strtol(args[1], &end, 0);
    //error handling for str to int
    if (*end != '\0')
    {
        fprintf(stderr, "pksh: bg: Argument for job number should be an integer\n");
        return;
    }

    struct jobNode *job = getHead();

    while (job != NULL)
    {
        if (job->jobnum == jobnum)
        {
            kill(job->pid, SIGCONT);
            return;
        }
        job = job->next;
    }

    fprintf(stderr, "pksh: bg: No job with given job number\n");

    return;
}