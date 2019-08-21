#include "execute.h"
#include <stdlib.h>

void execute(char **args)
{
    if(args[0]==NULL)
    {
        return;
    }
    else if(args[0]=="pwd")
    {
        exec_pwd(args);
    }
    return;
}