#include <unistd.h>
#include "init.h"
#include "shell.h"

void init()
{
    //Initialise home directory
    getcwd(HOME,4096);
    //Do possible error handling
    
    return;    
}