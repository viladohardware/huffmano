#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include <stdio.h>
#include <stdlib.h>
/*
Define o tipo abstrato 'huffman_tree', cujo a struct contém o item do nó, a frequência do nó no arquivo,
um ponteiro para o nó filho da esquerda e um ponteiro para o nó filho da direita.
*/
typedef struct huffman_tree
{
	unsigned char item;
	int frequency;
	struct huffman_tree* left;
	struct huffman_tree* right;

} huffman_tree;

/*
Cria um nó sem filhos e retorna o seu ponteiro.
*/
huffman_tree* create_leaf(unsigned char item, int frequency);

/*
Cria um nó com filhos e retorna o seu ponteiro.
 */
huffman_tree* create_parent(huffman_tree* left, huffman_tree* right);

/*
Procura por um elemento na árvore de huffman e retorna o seu ponteiro. Caso não existe, retorna NULL.
*/
huffman_tree* search(huffman_tree* huffman, unsigned char item);

/*
Imprime a árvore de huffman em pré-ordem.
*/
void print_pre_order (huffman_tree* huffman);

#endif
