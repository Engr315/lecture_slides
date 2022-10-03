#include <stdio.h>
#include <stdlib.h>


int main ()
{

    volatile int x = 3;

    while (x == 3) { ; }
    return 0;
}

