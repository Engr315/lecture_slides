#include <stdio.h>
#include <stdlib.h>

#include "foo.h"

int main()
{
    printf("Hello World\n");

    int a = foo(2,3);
    printf("A: %d\n", a);

    return 0;
}
