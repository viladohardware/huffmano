#include "../lib/bitmask.h"

int is_bit_set(unsigned char* c, int i, int size)
{
  return (c[i/(size*8)] & 1 << (i%(size*8))) != 0;
}

void set_bit(unsigned char* c, int i, int size)
{
  c[i/(size*8)] |= 1 << (i%(size*8));
}

void unset_bit(unsigned char* c, int i, int size)
{
  c[i/(size*8)] &= ~(1 << (i%(size*8)));
}

void print_bits(unsigned char* c, int size, int bits)
{
  int i;
  for(i = 0; i < bits; i++) printf("%d ",is_bit_set(c,i,size));
  printf("\n");
}
