#ifndef BITMASK_H
#define BITMASK_H

/*
  Muda o valor da variavel x em n bits para a esquerda.
*/
unsigned char shift_left(unsigned char x, int n);

/*
  Muda o valor da variavel x em n bits para a direita.
*/
unsigned char shift_right(unsigned char x, int n);

/*
  Verifica se o n-esimo bit está setado.
*/
int is_bit_set(unsigned char x, int n);

/*
  Seta o n-esimo bit.
*/
unsigned char set_bit(unsigned char x, int n);

#endif
