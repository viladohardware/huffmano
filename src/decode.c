#include "../lib/decode.h"
#include "../lib/get_header.h"

node* recovery_tree(unsigned char array[], int size)
{
	int i;
	node* now = NULL;
	stack* stack = create_stack();
	//array auxiliar marca 1 onde '\' e '*' são elementos da arvore.
	int aux[size];
	memset(aux, 0, sizeof aux);
	for (i=0; i < size; ++i)
	{
		if (array[i] == '\\')
		{
			++i;
			aux[i] = 1;
		}
	}

	for (i = size - 1; i >= 0; --i)
	{
		if (array[i] == '*')
		{
			if(aux[i] == 1)
			{
				now = new_node(array[i]);
				push(stack, now);
			}
			else
			{
				now = new_node(array[i]);
				now->left = pop(stack);
				now->right = pop(stack);
				push(stack, now);
			}
		}
		else if(array[i] == '\\')
		{
			if (aux[i] == 1)
			{
				now = new_node(array[i]);
				push(stack, now);
			}
		}
		else
		{
			now = new_node(array[i]);
			push(stack, now);
		}
	}
	return stack->top;
}

void decode(FILE* file, node *root, int trash_size)
{
	int i, j, read_size;
	unsigned char buffer[BUFFER_SIZE];//o valor de BUFFER_SIZE vem de um define! NESSE CASO 256
	node *tree;
	tree = root;
	//arquivo de saida
	FILE *descompressed;
	descompressed = fopen("descompressed", "wb");

  	while((read_size = fread(buffer, 1, BUFFER_SIZE,file)) >= 1)
	{
		for (i = 0; i < read_size; ++i)
		{
			int avoid_trash = 8;//valor que deverá ser usado onde não tiver lixo
			if ((read_size != BUFFER_SIZE) && ( i + 1 ==  read_size))
			{
				avoid_trash = (8 - trash_size);
			}
			for (j = 0; j < avoid_trash; ++j)
			{
				if (is_bit_set(&buffer[i], j))
				{
					tree = tree->right;
				}
				else
				{
					tree = tree->left;
				}
				if (tree->right == NULL && tree->left == NULL)
				{
					fputc(tree->item, descompressed);
					tree = root;
				}
			}
		}
	}
}
