#include "parse.h"
#include <string.h>

char **parse(char *string, char *delim)
{
    char **parsed_string = (char **)malloc(64 * sizeof(char **));
    int index = 0 ;
    char* token = strtok(string,delim) ;
    while(token !== NULL)
    {
        parsed_string[index] = token;
        index++;
        token = strtok(NULL,delim);
    }
    parsed_string[index] = NULL;
    return parsed_string;

}