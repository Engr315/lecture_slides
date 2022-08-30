
#include <stdio.h>
#include "popcount.h"

int main()
{
    int res,res2;
    for (int i = 0; i < 20; ++i){
        res = popcount(i);
        //res2 = popcount_asm(i);
        res2 = -1;
        printf ("i:%d i:0x%x c: %d asm:%d\n", i, i, res, res2);
    }

    int64_t i = -1; 
    res = popcount((uint64_t) i);
    //res2 = popcount_asm((uint64_t)i);
    res2 = -1;
    printf ("i:%lld i:0x%llx c: %d asm:%d\n", i, i, res, res2);
    return 0;
}
