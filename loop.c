#include <stdio.h>
#include "loop.h"
#include "shell.h"
#include "prompt.h"
#include "parse.h"

void loop()
{
    char *line;
    int linesize = 0;
    char **args;
    int status;
    char* delim = " \t\n\r\f";

    do
    {
        prompt();
        getline(&line, &linesize,stdin);
        char** commands = parse(line, ";");
        for(int i=0;i<sizeof(commands);i++)
        {
            if(commands[i]==NULL)
            {
                break;
            }
            //printf("%s\n",commands[i]);

            //parse by whitespace characters
            args = parse(commands[i], delim);
           

        }
        //printf("%s",line);
        status = 1;
    } while (status);
}