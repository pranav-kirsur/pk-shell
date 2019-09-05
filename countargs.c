#include "countargs.h"
#include <stdlib.h>

int countargs(char **args)
{
    int argc = 0;
    //iterate through args array
    for (int i = 0; i < sizeof(args); i++)
    {
        if (args[i] == NULL)
        {
            break;
        }
        else
        {
            argc++;
        }
    }
    return argc;
}