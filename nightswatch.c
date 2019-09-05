#include "nightswatch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

//get the dirty bits
char *get_dirty()
{
    FILE *memfile = fopen("/proc/meminfo", "r");
    char *line;
    size_t n = 0;
    for (int i = 0; i < 16; i++)
    {
        getline(&line, &n, memfile);
        free(line);
        n = 0;
    }

    getline(&line, &n, memfile);
    return line;
}

// detects key down
// Credits : stackoverflow
int keyDown()
{
    struct termios oldt, newt;
    int bytes;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ioctl(STDIN_FILENO, FIONREAD, &bytes);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return bytes > 0;
}

//waits for a number of seconds
int wait_seconds(int seconds)
{
    clock_t initial_clock = clock();
    while (clock() - initial_clock < seconds * CLOCKS_PER_SEC)
    {
        //do nothing
        if (keyDown())
        {
            if (getchar() == 'q')
            {
                //quit
                return 1;
            }
        }
    };
    // normal execution
    return 0;
}

void nightswatch(char **args)
{
    int num = 1;
    for (int i = 1; i < 3; i++)
    {
        if (args[i] == NULL)
        {
            fprintf(stderr, "Invalid number of arguments");
            return;
        }
    }
    num = atoi(args[2]);
    if (num < 1)
    {
        fprintf(stderr, "Invalid time argument");
        return;
    }
    if (strcmp(args[3], "dirty") == 0)
    {
        while (1)
        {
            printf("%s\n", get_dirty());
            if (wait_seconds(num) == 1)
            {
                return;
            }
        }
    }
    else
    {
        return;
    }
}