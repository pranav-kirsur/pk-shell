#ifndef __SHELL_H
#define __SHELL_H

/* Contains global variables */
char HOME[4096];
// struct that stores pid and name
struct pid_name
{
    int pid;
    char name[100];
};

//array of structs to store pid , name pairs
struct pid_name bg_proc_names[50];
int bg_process_index;

//struct to store command history
struct command_history_struct
{
    char command_history_array[20][1024];
    int command_history_index;
};

struct command_history_struct command_history;

//path to history file
char pksh_history_path[4096];

#endif
