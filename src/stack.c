#include "../lib/stack.h"

node* new_node (unsigned char item)
{
    node *temp = malloc(sizeof(node));;
    temp->item = item;
    temp->left = NULL;
    temp->right = NULL;
    temp->next = NULL;
    return temp;
}

pilha* criar_pilha()
{
	pilha *nova_pilha = (pilha*) malloc(sizeof(pilha));
	nova_pilha->top = NULL;
	nova_pilha->size = 0;
	return nova_pilha;
}

void push(pilha *pilha, node *node)
{
	node->next = pilha->top;
	pilha->top = node;
	pilha->size++;
}

node* pop(pilha *pilha)
{
	if (pilha->top == NULL)
	{
		printf("LISTA VAZIA\n");
		return NULL;
	}
	else
	{
		node *aux = pilha->top;
		pilha->top = pilha->top->next;
		pilha->size--;
		return aux;
	}
}
