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

stack* create_stack()
{
	stack *new = (stack*) malloc(sizeof(stack));
	new->top = NULL;
	new->size = 0;
	return new;
}

void push(stack* stack, node *node)
{
	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

node* pop(stack *stack)
{
	if (stack->top == NULL)
	{
		printf("LISTA VAZIA\n");
		return NULL;
	}
	else
	{
		node *aux = stack->top;
		stack->top = stack->top->next;
		stack->size--;
		return aux;
	}
}
