#include <stdio.h>
#include <stdlib.h>


int main ()
{

    volatile int x = 2;

    while (x == 2) { ; }
    return 0;
}

