#include "launch.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void launch(char **args)
{
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
        //we wait for child process to execute
        int status;
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return;
}