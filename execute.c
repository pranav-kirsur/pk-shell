#include "execute.h"
#include "exec_pwd.h"
#include "exec_cd.h"
#include "exec_echo.h"
#include "exec_ls.h"
#include "exec_pinfo.h"
#include "launch.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "history.h"
#include "nightswatch.h"
#include "exec_setenv.h"
#include "exec_unsetenv.h"
#include "exec_jobs.h"
#include "exec_kjob.h"
#include "exec_fg.h"
#include "exec_bg.h"
#include "overkill.h"
#include "quit.h"
#include "recall_history.h"

void execute(char **args)
{
    if (args[0] == NULL)
    {
        return;
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        exec_pwd(args);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        exec_cd(args);
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        exec_echo(args);
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        exec_ls(args);
    }
    else if (strcmp(args[0], "pinfo") == 0)
    {
        exec_pinfo(args);
    }
    else if (strcmp(args[0], "history") == 0)
    {
        history(args);
    }
    else if (strcmp(args[0], "nightswatch") == 0)
    {
        nightswatch(args);
    }
    else if (strcmp(args[0], "setenv") == 0)
    {
        exec_setenv(args);
    }
    else if (strcmp(args[0], "unsetenv") == 0)
    {
        exec_setenv(args);
    }
    else if (strcmp(args[0], "jobs") == 0)
    {
        exec_jobs(args);
    }
    else if (strcmp(args[0], "kjob") == 0)
    {
        exec_kjob(args);
    }
    else if (strcmp(args[0], "fg") == 0)
    {
        exec_fg(args);
    }
    else if (strcmp(args[0], "bg") == 0)
    {
        exec_bg(args);
    }
    else if (strcmp(args[0], "overkill") == 0)
    {
        overkill(args);
    }
    else if (strcmp(args[0], "quit") == 0)
    {
        quit(args);
    }
    //detect up arrow key
    else if (args[0][0] == '\033' && args[0][1] == '[' && args[0][2] == 'A')
    {
        recall_history(args);
        return;
    }
    else
    {
        launch(args);
    }

    return;
}