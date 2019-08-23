#include "exec_pinfo.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"

void exec_pinfo(char **args)
{
    int argc = 0;
    for (argc = 0; argc < sizeof(args); argc++)
    {
        if (args[argc] == NULL)
        {
            break;
        }
    }
    if (argc != 1 && argc != 2)
    {
        fprintf(stderr, "You must provide either 0 or 1 arguments\n");
        return;
    }
    char pid[100];
    if (argc == 1)
    {
        sprintf(pid, "%d", getpid());
    }
    else
    {
        strcpy(pid, args[1]);
    }

    // Check if PID exists
    char proc_path[1000];
    strcpy(proc_path, "/proc/");
    strcat(proc_path, pid);

    char exec_path[1000];
    strcpy(exec_path, proc_path);

    if (access(proc_path, F_OK | R_OK) == -1)
    {
        fprintf(stderr, "Given PID does not exist or shell does not have permissions to read /proc/\n");
        return;
    }
    //Read info from file
    strcat(proc_path, "/stat");
    FILE *stream;
    stream = fopen(proc_path, "r");
    if (stream == NULL)
    {
        perror("pksh: pinfo");
        return;
    }
    char *line;
    size_t n = 0;
    int getline_status = getline(&line, &n, stream);
    if (getline_status == -1)
    {
        perror("pksh: pinfo");
    }

    char **parsed_line = parse(line, " ");

    printf("PID -- %s\n", pid);
    printf("Process Status -- %s\n", parsed_line[2]);
    printf("Memory -- %s\n", parsed_line[22]);

    free(line);
    line = (char *)malloc(4096 * sizeof(char));
    strcat(exec_path, "/exe");

    if (readlink(exec_path, line, 4096) == -1)
    {
        perror("pksh: pinfo");
        return;
    }
    //This line is added to fix non null terminated bugs
    strcat(line, "\0");

    printf("Executable path -- %s\n", line);
    return;
}
