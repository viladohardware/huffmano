#ifndef BITMASK_H
#define BITMASK_H

/*
  Verifica se o i-esimo bit está setado. Retorna 1 para setado e 0 para não setado.
*/
int is_bit_set(unsigned char* c, int i, int size);

/*
  Seta o i-esimo bit como 1.
*/
void set_bit(unsigned char* c, int i, int size);

/*
  Seta o i-esimo bit como 0.
*/
void unset_bit(unsigned char* c, int i, int size);

/*
  Printa bits de uma série de bytes.
*/
void print_bits(unsigned char* c, int size, int bits);

#endif
