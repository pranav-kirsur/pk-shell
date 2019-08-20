#include <stdio.h>
#include "shell.h"
#include "init.h"
#include "loop.h"

int main()
{
    //Initialise the shell
    init();

    //performs shell read print eval for shell
    loop();

    return 0;
}