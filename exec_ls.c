#include "exec_ls.h"
#include "shell.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>

//filter function for scandir which outputs 1 for files not beginning with .
int filter(const struct dirent *file)
{
    if (file->d_name[0] == '.')
    {
        return 0;
    }
    return 1;
}

void exec_ls(char **args)
{
    //flags for l and a
    int l_flag_enabled = 0, a_flag_enabled = 0;

    //directory name set to current directory by default
    char *dir = ".";

    //scan arguments
    for (int i = 1; i < sizeof(args); i++)
    {
        if (args[i] == NULL)
        {
            break;
        }
        if (args[i][0] == '-')
        {
            for (int j = 1; j < strlen(args[i]); j++)
            {
                if (args[i][j] == 'l')
                {
                    l_flag_enabled = 1;
                }
                else if (args[i][j] == 'a')
                {
                    a_flag_enabled = 1;
                }
            }
        }
        else
        {
            dir = args[i];
        }
    }

    //set directory to HOME if set as ~
    if (strcmp(dir, "~") == 0)
    {
        dir = HOME;
    }

    //scan directory using scandir
    struct dirent **list_of_files;
    int number_of_files = 0;

    if (a_flag_enabled)
    {
        number_of_files = scandir(dir, &list_of_files, NULL, alphasort);
    }
    else
    {
        number_of_files = scandir(dir, &list_of_files, filter, alphasort);
    }

    //print list of files according to l_flag
    if (l_flag_enabled)
    {
        printf("total %d\n",number_of_files);
        

    }
    else
    {
        for (int i = 0; i < number_of_files; i++)
        {
            printf("%s\n", list_of_files[i]->d_name);
        }
    }

    return;
}
