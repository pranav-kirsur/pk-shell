#include "execute.h"
#include "exec_pwd.h"
#include "exec_cd.h"
#include "exec_echo.h"
#include "exec_ls.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void execute(char **args)
{
    if(args[0]==NULL)
    {
        return;
    }
    else if(strcmp(args[0],"pwd")==0)
    {
        exec_pwd(args);
    }
    else if(strcmp(args[0],"cd")==0)
    {
        exec_cd(args);
    }
    else if(strcmp(args[0],"echo")==0)
    {
        exec_echo(args);
    }
    else if(strcmp(args[0],"ls")==0)
    {
        exec_ls(args);
    }
    else
    {
        fprintf(stderr,"%s : Command not found",args[0]);
    }
    
    return;
}