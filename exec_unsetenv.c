#include "exec_unsetenv.h"
#include <stdio.h>
#include <stdlib.h>
#include "countargs.h"

void exec_unsetenv(char **args)
{
    //count arguments
    int argc = countargs(args);
    if(argc != 2)
    {
        //print error message
        fprintf(stderr,"unsetenv: Invalid number of arguments");
        return;
    }
    else
    {
        // unset env with error handling
        if(unsetenv(args[1])==-1)
        {
            perror("pksh: unsetenv");
        }
        
    }
    return;
    
}