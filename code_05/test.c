#include <stdio.h>
#include <inttypes.h>

#define REG_FOO 0x40000140

int main () {
  volatile uint32_t *reg = (uint32_t *)(REG_FOO);
  *reg += 3;

  printf("0x%x\n", *reg); // Prints out new value
}

