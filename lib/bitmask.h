#ifndef BITMASK_H
#define BITMASK_H

/*
  Verifica se o i-esimo bit (da esquerda para direita) está setado. Retorna 1 para setado e 0 para não setado.
*/
int is_bit_set(unsigned char* c, int i);

/*
  Seta o i-esimo (da esquerda para direita) bit como 1 em uma série de bytes.
*/
void set_bit(unsigned char* c, int i);

/*
  Seta o i-esimo (da direita para esquerda) bit como 1 em um byte.
*/
void set_bit_rl(unsigned char* c, int i);

/*
  Retorna o i-esimo (da esquerda para direita) bit como 0 em uma série de bytes.
*/
void unset_bit(unsigned char* c, int i);

/*
  Printa bits de uma série de bytes.
*/
void print_bits(unsigned char* c, int size);

#endif
