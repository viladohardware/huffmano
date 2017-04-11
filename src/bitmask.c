#include "../lib/bitmask.h"

int is_bit_set(unsigned char* c, int i)
{
  return (c[i/8] & 1 << (i%8)) != 0;
}

void set_bit(unsigned char* c, int i)
{
  c[i/8] |= 1 << (i%8);
}

void unset_bit(unsigned char* c, int i)
{
  c[i/8] &= ~(1 << (i%8));
}

void print_bits(unsigned char* c, int size)
{
  int i;
  for(i = 0; i < size*8; i++) printf("%d ",is_bit_set(c,i));
  printf("\n");
}
