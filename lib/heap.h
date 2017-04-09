#ifndef heap_h
#define heap_h
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 256

/*
	Define o tipo abstrato 'heap', cujo a struct contém
	o tamanho atual da heap, e um array com seu tamanho máximo
*/
typedef struct heap
{
	int size;
	huffman_tree* node[MAX_SIZE+1];
} heap;

/*
	Aloca a heap na memória, inicializa os ponteiros do array e o tamanho da heap
*/
heap* create_heap();

/*
	Recebe um indice do array, e retorna o pai do nó correspondente 
*/
int get_parent_index(heap* heap, int index);

/*
	Recebe um indice do array, e retorna o filho da esquerda do nó correspondente 
*/
int get_left_index(heap* heap, int index);

/*
	Recebe um indice do array, e retorna o filho da direita do nó correspondente  
*/
int get_right_index(heap* heap, int index);

/*
	Verifica se a heap está vazia. Se sim, retorna 1, caso contrário retorna 0.
*/
int is_empty(heap *heap);

/*
	Recebe dois ponteiros e troca seus valores
*/
void swap(huffman_tree* a, huffman_tree* b);

/*
	Serve para manter a propriedade da min_heap, no qual todos os nós devem ser maiores ou iguais aos seus pais (exceto a raíz).
	Recebe um indice e o compara com os valores da direita e esquerda para verificar qual o menor, depois, troca seus valores, até o valor
	do índice ficar na posição correta da heap.
*/
void min_heapify(heap *heap, int index);

/*
Enfileira um novo valor na heap, se valendo da propriedade da min_heap.
*/
void enqueue(heap *heap, huffman_tree* leaf);

/*
	Desenfileira o menor elemento da heap (fila de prioridade) e retorna o item que foi retirado
*/
huffman_tree* dequeue(heap* heap);

/*
	Recebe um array de inteiros com a frequência de todos os caracteres da entrada, e retorna a árvore de huffman montada
*/
huffman_tree* build_huffman_tree(int* freq);

/*
	Imprime a heap
*/
void print_heap(heap* heap);

#endif