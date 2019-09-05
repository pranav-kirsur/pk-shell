#include "exec_setenv.h"
#include "countargs.h"
#include <stdio.h>
#include <stdlib.h>

void exec_setenv(char **args)
{
    int argc = countargs(args);
    // if number of args is not 2 or 3 print error (as name of command is one of the arguments)
    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "setenv: Invalid number of arguments\n");
        return;
    }
    // if one arg
    if (argc == 2)
    {
        //use setenv to overwrite env variable
        if (setenv(args[1], "", 1) == -1)
        {
            //error handling
            perror("pksh: setenv");
        }
    }
    // if two args
    if (argc == 3)
    {
        //use setenv to overwrite env variable

        if (setenv(args[1], args[2], 1) == -1)
        {
            //error handling
            perror("pksh: setenv");
        }
    }
    return;
}