#include "exec_pwd.h"
#include <unistd.h>
#include <stdio.h>

void exec_pwd(char **args)
{
    char currentpath[4096];
    getcwd(currentpath, 4096);
    printf("%s\n", currentpath);
    return;
}