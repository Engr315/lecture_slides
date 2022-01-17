
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

