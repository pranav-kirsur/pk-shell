#include "launch.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        args[i-1] = NULL;
    }

    int pid;
    //fork the process
    pid = fork();

    if (pid == 0)
    {
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
            int status;
            do
            {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
    return;
}