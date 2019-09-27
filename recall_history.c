#include "recall_history.h"
#include "countargs.h"
#include "shell.h"
#include "parse.h"
#include "execute_pipeline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void recall_history(char **args)
{
    if (countargs(args) != 1)
    {
        fprintf(stderr, "Invalid up arrow key sequence : more than 1 argument\n");
        return;
    }

    int num_up_arrows = 0;
    if (strlen(args[0]) % 3 != 0)
    {
        fprintf(stderr, "Invalid up arrow key sequence: invalid length\n");
        return;
    }

    //scan for invalid characters in input
    for (int i = 0; i < strlen(args[0]); i++)
    {
        if (args[0][i] != '\033' && args[0][i] != '[' && args[0][i] != 'A')
        {
            fprintf(stderr, "Invalid up arrow key sequence: invalid character\n");
            return;
        }
    }

    //count number of up arrow keys
    for (int i = 0; i < strlen(args[0]); i += 3)
    {
        if (args[0][i] == '\033' && args[0][i + 1] == '[' && args[0][i + 2] == 'A')
        {
            num_up_arrows++;
        }
        else
        {
            fprintf(stderr, "Invalid up arrow key sequence \n");
            return;
        }
    }

    if (num_up_arrows > 10)
    {
        fprintf(stderr, "Too many up arrow keys\n");
        return;
    }

    char *line = (char *)malloc(1024 * sizeof(char));
    line[0] = '\0';

    //get command from history
    strcpy(line, command_history.command_history_array[(command_history.command_history_index - num_up_arrows + 1) % 20]);

    if (strlen(line) == 0)
    {
        return;
    }

    //print the line
    printf("%s\n",line);

    //execute command from history
    char **commands = parse(line, ";");
    for (int i = 0; i < sizeof(commands); i++)
    {
        if (commands[i] == NULL)
        {
            break;
        }

        //parse by pipe symbol
        args = parse(commands[i], "|");
        execute_pipeline(args);
    }
    return;
}