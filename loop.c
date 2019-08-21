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

    do
    {
        prompt();
        getline(&line, &linesize,stdin);
        char** commands = parse(line, ";");

        //printf("%s",line);
        status = 1;
    } while (status);
}