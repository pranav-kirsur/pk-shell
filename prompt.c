#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "prompt.h"
#include "shell.h"

void prompt()
{
    //get variables
    char *user = getenv("USER");
    char hostname[1024];
    gethostname(hostname, 1024);
    char current_directory[4096];
    getcwd(current_directory, 4096);

    //print prompt
    printf("\n>%s@%s:%s",user,hostname,current_directory);
}