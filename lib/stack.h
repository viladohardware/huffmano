#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node
{
 	unsigned char item;
  	struct node* left;
	struct node* right;
 	struct node *next;
}node;

typedef struct stack
{
	node *top;
	int size;
}stack;

/*
	Cria o tipo abstrato 'node' onde a struct contém um node de uma Árvore preparado para ser usado em uma pilha.
*/
node* new_node (unsigned char item);

/*
	Cria uma pilha vazia.
*/
stack* create_stack();

/*
	Adiciona um elemento no topo da pilha.
*/
void push(stack* stack, node *node);

/*
	Retira o elemento no topo da pilha.
*/
node* pop(stack* stack);

#endif
