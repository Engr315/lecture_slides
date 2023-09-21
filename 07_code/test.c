#include <stdio.h>
#include <inttypes.h>

#define REG_FOO 0x40000140

void noquit(void);

int main () {
  volatile uint32_t *reg = (uint32_t *)(REG_FOO);
  *reg += 3;

  printf("0x%x\n", *reg); // Prints out new value

  //noquit();
  //noquit_volatile();

}

void noquit () {
    int y = 0;

    int quit = y;
    while (!quit)
    {
        //other code
        quit = y;
    }
}

void noquit_volatile () {
    volatile int y = 0;

    int quit = y;
    while (!quit)
    {
        //other code
        quit = y;
    }
}

