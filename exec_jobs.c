#include "exec_jobs.h"
#include "shell.h"
#include "linkedlist.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void exec_jobs(char **args)
{
    struct jobNode *job = getHead();
    while (job != NULL)
    {
        //get job pid from job
        int pid = job->pid;

        //read status from /proc/<pid>/stat
        char proc_path[1000];
        sprintf(proc_path,"/proc/%d/stat",pid);

        FILE *stream;
        stream = fopen(proc_path, "r");

        char *line;
        size_t n = 0;
        getline(&line, &n, stream);
        char **parsed_line = parse(line, " ");

        //set status string
        char status[50] = "Running";
        if (strcmp(parsed_line[2], "T") == 0)
        {
            strcpy(status, "Stopped");
        }

        //print job description
        printf("[%d] %s %s [%d]\n", job->jobnum, status, job->name, job->pid);

        //iterate to next job
        job = job->next;
    }
    return;
}