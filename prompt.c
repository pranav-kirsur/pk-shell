#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    //check if current directory is child of ~
    int size_of_home = strlen(HOME);
    if(strncmp(HOME,current_directory,size_of_home)==0)
    {
        char relative_current_directory[4096];
        relative_current_directory[0]='~';
        relative_current_directory[1]='\0';
        strcat(relative_current_directory,current_directory+size_of_home);
        strcpy(current_directory,relative_current_directory);   
    }

    //print prompt
    printf(">%s@%s:%s $ ",user,hostname,current_directory);
}