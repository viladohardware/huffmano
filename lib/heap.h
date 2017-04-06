#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

/*
Define o tipo abstrato 'heap', cujo a struct contém
o tamanho atual da heap, e um array com seu tamanho máximo
*/
typedef struct heap
{
	int size;
	int data[MAX_SIZE];
} heap;

/*
 Aloca a heap na memória e inicializa seu tamanho em 0
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
Recebe um índice e retorna o valor correspondente na heap
*/
int item_of(heap *heap, int index);

/*
Verifica se a heap está vazia. Se sim, retorna 1, caso contrário retorna 0.
*/
int is_empty(heap *heap);

/*
Recebe dois ponteiros e troca seus valores
*/
void swap(int* a, int* b);

/*
Ordena o array da heap em O(log(n))
*/
void heapsort(heap *heap);

/*
 Serve para manter a propriedade da min_heap, no qual todos os nós devem ser maiores ou iguais aos seus pais (exceto a raíz).
 Recebe um indice e o compara com os valores da direita e esquerda para verificar qual o menor, depois, troca seus valores, até o valor
 do índice ficar na posição correta da heap.
*/
void min_heapify(heap *heap, int index);

/*
Enfileira um novo valor na heap, se valendo da propriedade da min_heap.
*/
void enqueue(heap *heap, int item);

/*
Desenfileira o menor elemento da heap (fila de prioridade) e retorna o item que foi retirado
*/
int dequeue(heap* heap);

/*
Imprime a heap
*/
void print_heap(heap* heap)