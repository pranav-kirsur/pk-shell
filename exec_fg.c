#include "exec_fg.h"
#include "shell.h"
#include "linkedlist.h"
#include "countargs.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

void exec_fg(char **args)
{
    int argc = countargs(args);
    if (argc != 2)
    {
        fprintf(stderr, "pksh: fg: Invalid number of arguments\n");
        return;
    }

    char *end;
    int jobnum = strtol(args[1], &end, 0);
    //error handling for str to int
    if (*end != '\0')
    {
        fprintf(stderr, "pksh: fg: Argument for job number should be an integer\n");
        return;
    }

    struct jobNode *job = getHead();
    while (job != NULL)
    {
        if (job->jobnum == jobnum)
        {
            //sets process group of formerly bg process to be same as that of parent shell
            setpgid(job->pid, getpgid(0));
            int pid = job->pid;

            //remove process from jobs linked list
            deleteJobNode(pid);

            //mute terminal input/output signals for the shell
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            //set child process group as foreground
            tcsetpgrp(STDIN_FILENO, pid);

            //send continue signal to process
            kill(pid, SIGCONT);

            //wait for process to finish (foreground process)
            int status;
            do
            {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));

            //set parent process group as foreground
            tcsetpgrp(STDIN_FILENO, getpgrp());

            //set up signals again
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            return;
        }
        job = job->next;
    }

    fprintf(stderr, "No such job with given job number found\n");

    return;
}
