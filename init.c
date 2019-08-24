#include <unistd.h>
#include <signal.h>
#include "bg_terminate.h"
#include "init.h"
#include "shell.h"

void init()
{
    //Initialise home directory
    getcwd(HOME, 4096);

    //Attach signal handler for when background process quits
    signal(SIGCHLD, bg_terminate);

    //Initialise array for storing background process names
    // Support upto 50 background processes

    for (int i = 0; i < 50; i++)
    {
        bg_proc_names[i].pid = -1;
    }

    //Initialise bg process index
    bg_process_index = 0;

    return;
}