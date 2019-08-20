#include "loop.h"
#include "shell.h"
#include "prompt.h"

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