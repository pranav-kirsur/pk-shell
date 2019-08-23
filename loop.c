#include <stdio.h>
#include <stdlib.h>
#include "loop.h"
#include "shell.h"
#include "prompt.h"
#include "parse.h"
#include "execute.h"

void loop()
{
    char *line =(char *) malloc(1024 * sizeof(char));
    size_t linesize = 1024;
    char **args;
    int status;
    char *delim = " \t\n\r\f";

    do
    {
        prompt();
        getline(&line, &linesize, stdin);
        char **commands = parse(line, ";");
        for (int i = 0; i < sizeof(commands); i++)
        {
            if (commands[i] == NULL)
            {
                break;
            }
            //printf("Command:%s\n",commands[i]);    
            //parse by whitespace characters
            args = parse(commands[i], delim);
            execute(args);
        }
        
        status = 1;
    } while (status);
}