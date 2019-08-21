#include "exec_echo.h"
#include <stdio.h>


//No support for quoting and stuff
void exec_echo(char **args)
{
    for(int i=1;i<sizeof(args);i++)
    {
        if(args[i]==NULL)
        {
            break;
        }
        printf("%s ",args[i]);
    }
    printf("\n");
    return;

}
