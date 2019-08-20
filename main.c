#include <stdio.h>


char* HOME[1024];

int main()
{
    //Initialise the shell
    init();

    //performs shell read print eval for shell
    loop();

    return 0;
}