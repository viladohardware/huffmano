#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
 	unsigned char item;
 	struct node *next;
}node;
typedef struct pilha
{
	node *top;
	int size;
}pilha;
/*
	Cria a pilha, com ponteiro top apontando para NULL e o size sendo 0. Retorna um ponteiro pilha.
*/
pilha* criar_pilha();
/*
	Adiciona um node no topo da pilha e incrementa o size em 1
*/
void push(pilha *pilha, unsigned char item);
/*
	Adiciona um node no topo da pilha e incrementa o size em 1
*/
void push(pilha *pilha, unsigned char item);
/*
	Caso a pilha não esteja vazia: adiciona um node no topo da lista e incrementa em 1 o size. Caso contrário: retorna -1(EOF)
*/
unsigned char pop(pilha *pilha);
/*
	Retorna o item que é um unsigned char, caso a lista não esteja vazia, se estive vazia retorna -1(EOF)
*/
unsigned char peek(pilha *pilha);
/*
	Retorna 1 se tiver vazia e 0 se não tiver  
*/
int is_empty(pilha *pilha);
#endif