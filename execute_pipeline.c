#include "execute_pipeline.h"
#include "countargs.h"
#include "execute_command.h"
#include "parse.h"
#include <unistd.h>

void execute_pipeline(char **commands)
{
    //whitespace delimeters
    char *delim = " \t\n\r\f";

    //number of commands in pipeline
    int n = countargs(commands);
    if (n == 0)
    {
        //empty command
        return;
    }
    if (n == 1)
    {
        //no pipes
        execute_command(parse(commands[0], delim), 0, 1);
        return;
    }
    else
    {
        int pipefd[2];
        int input = 0;

        //number of pipes will be one less
        for (int i = 0; i < n - 1; i++)
        {
            //create a pipe
            pipe(pipefd);

            //execute command with given input and output
            execute_command(parse(commands[i], delim), input, pipefd[1]);

            //close the write end of the pipe
            close(pipefd[1]);

            //change input to read end of pipe for next iteration
            input = pipefd[0];
        }

        //last command in the pipeline outputs to stdout
        execute_command(parse(commands[n - 1], delim), input, 1);
    }
    return;
}