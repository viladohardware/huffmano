#include "../lib/bitmask.h"

int is_bit_set (unsigned char* c, int i)
{
    if((128 >> (i%8) & c[i/8])) return 1;
    return 0;
}

void set_bit(unsigned char* c, int i)
{
	c[i/8] |= 128 >> (i%8);
}

void set_bit_rl(unsigned char* c, int i)
{
	*c |= 1<<i;
}

void unset_bit(unsigned char* c, int i)
{
	c[i/8] &= ~(128 >> (i%8));
}

void print_bits(unsigned char* c, int size)
{
  int i;
  for(i = 0; i < size*8; i++) printf("%d ",is_bit_set(c,i));
  printf("\n");
}
