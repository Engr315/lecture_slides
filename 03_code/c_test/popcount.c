
//https://en.wikipedia.org/wiki/Hamming_weight
#include "popcount.h"

int popcount(uint64_t num)
{
    int w=0;
    while (num) {
        w +=1;
        num &= (num -1);
    }
    return w;
}

//int popcount_asm(uint64_t num)
//{
//    uint64_t result;
//    asm (
//        "POPCNT %1, %0   \n"
//        : "=r" (result)
//        : "mr" (num)
//        : "cc"
//    );
//    return result;
//}

//
//int popcount_asm2(uint64_t num)
//{
//    register int low = num & 0xffffffff;
//    register int up = (num>>32);
//    register int rlow, rup;
//    asm (   
//        "POPCNT %1, %0   \n"
//        : "=r" (rlow)
//        : "mr" (low)
//        : "cc"
//    );
//    asm (   
//        "POPCNT %1, %0   \n"
//        : "=r" (rup)
//        : "mr" (up)
//        : "cc"
//    );
//
//    return rlow + rup;
//}

