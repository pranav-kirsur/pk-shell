#include "execute_command.h"
#include "execute.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void execute_command(char **args)
{

    //duplicate stdin and stdout descriptors to restore them later
    int stdin_fd = dup(0);
    int stdout_fd = dup(1);

    char **cleanedupargs = (char **)malloc(64 * sizeof(char **));
    int cleanedupargs_index = 0;

    for (int i = 0; i < sizeof(args); i++)
    {
        if (args[i] == NULL)
        {
            break;
        }

        //stdin from file
        if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1] != NULL)
            {

                int fd = open(args[i + 1], O_RDONLY);
                if (fd == -1)
                {
                    //restore the file descriptors
                    dup2(stdin_fd, 0);
                    dup2(stdout_fd, 1);
                    close(stdin_fd);
                    close(stdout_fd);

                    perror("pksh");
                    return;
                }

                //replace stdin with open file
                dup2(fd, 0);

                //close unused file descriptor
                close(fd);

                //go ahead two steps
                i += 2;
            }
            else
            {
                //restore the file descriptors
                dup2(stdin_fd, 0);
                dup2(stdout_fd, 1);
                close(stdin_fd);
                close(stdout_fd);

                fprintf(stderr, "No input file specified\n");
                return;
            }
        }

        //stdout from file
        else if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1] != NULL)
            {

                int fd = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd == -1)
                {
                    //restore the file descriptors
                    dup2(stdin_fd, 0);
                    dup2(stdout_fd, 1);
                    close(stdin_fd);
                    close(stdout_fd);

                    perror("pksh");
                    return;
                }

                //replace stdout with open file
                dup2(fd, 1);

                //close unused file descriptor
                close(fd);

                //go ahead two steps
                i += 2;
            }
            else
            {
                //restore the file descriptors
                dup2(stdin_fd, 0);
                dup2(stdout_fd, 1);
                close(stdin_fd);
                close(stdout_fd);

                fprintf(stderr, "No output file specified\n");
                return;
            }
        }

        //append
        else if (strcmp(args[i], ">>") == 0)
        {
            if (args[i + 1] != NULL)
            {

                int fd = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
                if (fd == -1)
                {
                    //restore the file descriptors
                    dup2(stdin_fd, 0);
                    dup2(stdout_fd, 1);
                    close(stdin_fd);
                    close(stdout_fd);

                    perror("pksh");
                    return;
                }

                //replace stdout with open file
                dup2(fd, 1);

                //close unused file descriptor
                close(fd);

                //go ahead two steps
                i += 2;
            }
            else
            {
                //restore the file descriptors
                dup2(stdin_fd, 0);
                dup2(stdout_fd, 1);
                close(stdin_fd);
                close(stdout_fd);

                fprintf(stderr, "No output file specified\n");
                return;
            }
        }
        else
        {
            cleanedupargs[cleanedupargs_index] = args[i];
            cleanedupargs_index++;
        }
    }

    cleanedupargs[cleanedupargs_index] = NULL;

    //execute with the arguments
    execute(cleanedupargs);

    //restore the file descriptors
    dup2(stdin_fd, 0);
    dup2(stdout_fd, 1);
    close(stdin_fd);
    close(stdout_fd);

    return;
}