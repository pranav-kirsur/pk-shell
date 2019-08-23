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

    return;
}