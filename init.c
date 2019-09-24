#include <unistd.h>
#include <signal.h>
#include "bg_terminate.h"
#include "init.h"
#include "shell.h"
#include "sighandlers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init()
{
    //Initialise home directory
    getcwd(HOME, 4096);

    //Attach signal handler for when background process quits
    signal(SIGCHLD, bg_terminate);

    //Attach signal handler for Ctrl + C (SIGINT) , ie ignore it
    signal(SIGINT,siginthandler);

    //Initialise array for storing background process names
    // Support upto 50 background processes

    for (int i = 0; i < 50; i++)
    {
        bg_proc_names[i].pid = -1;
    }

    //Initialise bg process index
    bg_process_index = 0;

    //Initialise history array from file if exists
    strcpy(pksh_history_path, HOME);
    strcat(pksh_history_path, "/.pksh_history");

    FILE *stream = fopen(pksh_history_path, "r");
    if (stream == NULL)
    {
        //initialize to defaults
        for (int i = 0; i < 20; i++)
        {
            strcpy(command_history.command_history_array[i], "\0");
        }
        command_history.command_history_index = 19;
    }
    else
    {
        //read struct from file
        fread(&command_history, 1,sizeof(struct command_history_struct) ,stream);
        fclose(stream);
    }

    return;
}