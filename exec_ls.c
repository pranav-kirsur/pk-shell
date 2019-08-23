#include "exec_ls.h"
#include "shell.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>

char *checkpermissions(char *filepath)
{
    struct stat filedetails;
    if (stat(filepath, &filedetails) == -1)
    {
        perror("pksh: ls");
        //return NULL if stat can't get the file
        return NULL;
    }
    char *permissions;

    permissions = (char *)malloc(11 * sizeof(char));
    mode_t mode = filedetails.st_mode;
    if (S_ISDIR(mode))
        permissions[0] = 'd';
    else if (S_ISLNK(mode))
        permissions[0] = 'l';
    else
        permissions[0] = '-';
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    return permissions;
}

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
    if (number_of_files == -1)
    {
        perror("pksh: ls");
        return;
    }
    //print list of files according to l_flag
    if (l_flag_enabled)
    {
        for (int i = 0; i < number_of_files; i++)
        {
            char *filepath = (char *)malloc(4096 * sizeof(char));
            strcpy(filepath, dir);
            strcat(filepath, "/");
            strcat(filepath, list_of_files[i]->d_name);

            //get file permissions
            char *permissions = checkpermissions(filepath);
            struct stat filedetails;

            int stat_status = stat(filepath, &filedetails);
            if (stat_status == -1)
            {
                perror("pksh: ls");
            }
            int hardlink_number = filedetails.st_nlink;

            //get owner and group name
            char *owner = getpwuid(filedetails.st_uid)->pw_name;
            char *group = getgrgid(filedetails.st_gid)->gr_name;

            int size = filedetails.st_size;
            char *time = (char *)malloc(100 * sizeof(char));
            strftime(time, 100, "%b %d %H:%M", localtime(&(filedetails.st_ctime)));

            printf("%s\t%d\t%s\t%s\t%d\t%s\t%s\n", permissions, hardlink_number, owner, group, size, time, list_of_files[i]->d_name);
            free(filepath);
            free(time);
            free(permissions);
        }
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
