#include "sighandlers.h"
#include "shell.h"
#include "linkedlist.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

//for Ctrl + C
void siginthandler(int signum)
{
    foreground_process_pid = -1;
    return;
}

//for Ctrl + Z
void sigtstphandler(int signum)
{
    
    if (foreground_process_pid == -1)
    {
        return;
    }

    //add new bg job to linked list
    struct jobNode *job = createJobNode(foreground_process_pid, foreground_process_name);
    addJobNode(job);

    //stop the process
    kill(foreground_process_pid, SIGTSTP);

    //since process has been moved to background
    foreground_process_pid = -1;

    return;
}