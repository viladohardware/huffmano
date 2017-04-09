#include "../lib/bitmask.h"

unsigned char shift_left(unsigned char x, int n)
{
  return x << n;
}

unsigned char shift_right(unsigned char x, int n)
{
  return x >> n;
}

int is_bit_set(unsigned char x, int n)
{
  unsigned char mask = 1 << n;
  return mask & x;
}

unsigned char set_bit(unsigned char x, int n)
{
  unsigned char mask = 1 << n;
  return mask | x;
}
