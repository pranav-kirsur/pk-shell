#include "loop.h"
#include "shell.h"

void loop()
{
    char *line;
    char **args;
    int status;

    do
    {
        prompt();
        status = 1;
    } while (status);
}