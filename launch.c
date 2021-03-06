#include "launch.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include "linkedlist.h"

void launch(char **args)
{
    //We first determine if the process should be run in the background
    int is_bg = 0;
    int i;
    for (i = 0; i < sizeof(args); i++)
    {
        if (args[i] == NULL)
        {
            break;
        }
    }
    //If & is at end make it a background process
    if (strcmp(args[i - 1], "&") == 0)
    {
        is_bg = 1;
        args[i - 1] = NULL;
    }

    int pid;
    //fork the process
    pid = fork();

    if (pid == 0)
    {
        //move bg process to its own process group
        setpgid(0, 0);

        //we are in child process
        if (execvp(args[0], args) == -1)
        {
            //There was an error
            perror("pksh ");
            //terminate with failure
            exit(EXIT_FAILURE);
        }
        //just in case code reaches here
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        //Error: Display error message
        perror("pksh ");
    }
    else
    {
        //we are in parent process
        //we wait for child process to execute if process is foreground
        if (!is_bg)
        {
            //set pid of current process as foreground process
            foreground_process_pid = pid;

            //set foreground process name
            strcpy(foreground_process_name, args[0]);

            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(STDIN_FILENO, pid);

            int status;
            do
            {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));

            tcsetpgrp(STDIN_FILENO, getpgid(0));
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            if (WIFSTOPPED(status))
            {
                if (foreground_process_pid != -1)
                {
                    //add to jobs
                    struct jobNode *job = createJobNode(foreground_process_pid, foreground_process_name);
                    addJobNode(job);
                }
            }
        }
        else
        {
            //store process name and pid in array
            if (bg_process_index < 50)
            {
                bg_proc_names[bg_process_index].pid = pid;
                strcpy(bg_proc_names[bg_process_index].name, args[0]);
                bg_process_index++;
            }
            //also add background process to linked list
            struct jobNode *bg_proc_job = createJobNode(pid, args[0]);
            addJobNode(bg_proc_job);
        }
    }
    return;
}