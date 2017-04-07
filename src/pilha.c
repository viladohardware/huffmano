#include "../lib/pilha.h"
pilha* criar_pilha()
{
	pilha *nova_pilha = (pilha*) malloc(sizeof(pilha));
	nova_pilha->top = NULL;
	nova_pilha->size = 0;
	return nova_pilha;
}
void push(pilha *pilha, unsigned char item)
{
	node *novo_topo = (node*) malloc(sizeof(node));
	novo_topo-> item = item;
	novo_topo->next = pilha->top;
	pilha->top = novo_topo;
	pilha->size++;
}
unsigned char pop(pilha *pilha)
{
	if (pilha->top == NULL)
	{
		return -1;
	}
	else
	{
		node *aux = pilha->top;
		unsigned char retorno = pilha->top->item;
		pilha->top = pilha->top->next;
		pilha->size--;
		free(aux);
		return retorno;	
	}
}
unsigned char peek(pilha *pilha)
{
	if (pilha->top == NULL)
	{
		return -1;
	}
	else
	{
		return pilha->top->item;	
	}
}
int is_empty(pilha *pilha)
{
	if(pilha->top == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
