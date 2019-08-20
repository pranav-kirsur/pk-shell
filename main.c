#include <stdio.h>


char* HOME[1024];

int main()
{
    //Initialise the shell
    pksh_init()

    //performs shell read print eval for shell
    pksh_loop();

    return 0;
}