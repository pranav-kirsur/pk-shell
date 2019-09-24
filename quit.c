#include "quit.h"
#include "countargs.h"
#include <stdio.h>
#include <stdlib.h>

void quit(char **args)
{
    if (countargs(args) != 1)
    {
        fprintf(stderr, "pksh: quit take no arguments\n");
        return;
    }

    //exit with a zero exit code
    exit(0);
}