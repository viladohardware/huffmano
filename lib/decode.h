#ifndef DECODE_H
#define DECODE_H
#include "stack.h"
#include "bitmask.h"
#define BUFFER_SIZE 256

/*
	Dado uma string com a pre-ordem de uma Árvore e seu tamanho retorna um ponteiro para node, com a árvore reconstruida
*/
node* recovery_tree(unsigned char array[], int size);

/*
	Dado um ponteiro para FILE, a árvore reconstruida, tamanho do lixo e tamanho da Árvore, cria o arquivo descompactado
*/
void decode(FILE* file, node *raiz, int tam_lixo, int tam_arvore);

#endif
