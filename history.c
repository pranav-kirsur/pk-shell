#include "history.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

void history(char **args)
{
    //Number of commands history ouptuts
    int num = 10;
    if (args[1] == NULL)
    {
        num = 10;
    }
    else
    {
        num = atoi(args[1]);
    }
    if (num > 10 || num < 0)
    {
        fprintf(stderr,"\nArgument to history should be an integer between 0 and 10\n");
        return;
    }
    for(int i = 0; i < num; i++)
    {
        printf("%s\n", command_history.command_history_array[(command_history.command_history_index - i + 20 ) % 20 ]);
    }
    return;
}