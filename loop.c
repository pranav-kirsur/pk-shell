#include <stdio.h>
#include "loop.h"
#include "shell.h"
#include "prompt.h"

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
        printf("%s",line);
        status = 1;
    } while (status);
}