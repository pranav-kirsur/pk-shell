#include <stdio.h>
#include <stdlib.h>
#include "loop.h"
#include "shell.h"
#include "prompt.h"
#include "parse.h"
#include "execute.h"
#include <fcntl.h>
#include <string.h>

void loop()
{
    char *line = (char *)malloc(1024 * sizeof(char));
    size_t linesize = 1024;
    char **args;
    int status;
    char *delim = " \t\n\r\f";

    do
    {
        prompt();
        getline(&line, &linesize, stdin);

        //add line to history
        command_history.command_history_index = (command_history.command_history_index + 1) % 20;
        strcpy(command_history.command_history_array[command_history.command_history_index], line);

        char **commands = parse(line, ";");
        for (int i = 0; i < sizeof(commands); i++)
        {
            if (commands[i] == NULL)
            {
                break;
            }

            //parse by whitespace characters
            args = parse(commands[i], delim);
            execute(args);
        }

        status = 1;
    } while (status);
}