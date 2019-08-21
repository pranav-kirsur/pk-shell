#include "execute.h"
#include <stdlib.h>
#include <string.h>

void execute(char **args)
{
    if(args[0]==NULL)
    {
        return;
    }
    else if(strcmp(args[0],"pwd"))
    {
        exec_pwd(args);
    }
    return;
}