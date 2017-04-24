#ifndef GET_HEADER_H
#define GET_HEADER_H

#include <stdio.h>
#include <math.h>

/*
Verifica se o arquivo foi aberto corretamente
*/
void open(FILE* file);

/*
Retorna o tamanho do lixo
*/
int trash(FILE* file);

/*
Retorna o tamanho da árvore
*/
int tree_size(FILE* file);

/*
Retorna um array com a árvore em pre-order
*/
unsigned char* pre_order_tree(FILE* file, int tree_size);
#endif
