#include "quit.h"
#include "countargs.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void quit(char **args)
{
    if (countargs(args) != 1)
    {
        fprintf(stderr, "pksh: quit take no arguments\n");
        return;
    }

    //save history in file
    FILE *stream = fopen(pksh_history_path, "w");
    fwrite(&command_history, 1, sizeof(struct command_history_struct), stream);
    fclose(stream);

    //exit with a zero exit code
    exit(0);
}