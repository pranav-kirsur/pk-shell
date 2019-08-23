#include "exec_cd.h"
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#include <string.h>

void exec_cd(char **args)
{
    if (args[1] == NULL)
    {
        chdir(HOME);
    }
    else if (strcmp(args[1], "~") == 0)
    {
        chdir(HOME);
    }
    else
    {
        if (chdir(args[1]) == -1)
        {
            //Show error message
            perror("pksh: cd");
        }
    }

    return;
}