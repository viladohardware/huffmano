#ifndef REBUILD_TREE_H
#define REBUILD_TREE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree
{
	unsigned char item;
	struct binary_tree* left;
	struct binary_tree* right;

} binary_tree;

/*
	Essa função recebe um ponteiro para árvore, array como os elementos da árvore de huffman em pré-ordem e um inteiro.
	Usamos os dois primeiros para remontar a árvore de huffman e retorna-lá. Já o inteiro nivel serve para zerar a variável
  estática após a reconstrução da árvore.
*/
binary_tree* rebuild_tree(binary_tree* ht, unsigned char* key, int nivel);

void print_pre_order (binary_tree* bt);

int is_empty_tree(binary_tree* bt);

binary_tree* create_empty_binary_tree();

#endif
