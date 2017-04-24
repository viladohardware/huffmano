#include "../lib/decode.h"
#include "../lib/get_header.h"

node* recovery_tree(unsigned char array[], int size)
{
	int i;
	node* atual = NULL;
	pilha* pilha = criar_pilha();
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
				atual = new_node(array[i]);
				push(pilha, atual);
			}
			else
			{
				atual = new_node(array[i]);
				atual->left = pop(pilha);
				atual->right = pop(pilha);
				push(pilha, atual);
			}
		}
		else if(array[i] == '\\')
		{
			if (aux[i] == 1)
			{
				atual = new_node(array[i]);
				push(pilha, atual);
			}
		}
		else
		{
			atual = new_node(array[i]);
			push(pilha, atual);
		}
	}
	return pilha->top;
}

void decode(FILE* file, node *raiz, int tam_lixo, int tam_arvore)
{
	int i, j, tam_lido;
	unsigned char buffer[BUFFER_SIZE];//o valor de BUFFER_SIZE vem de um define! NESSE CASO 256
	node *arvore;
	arvore = raiz;
	//arquivo de saida
	FILE *descompactado;
	descompactado = fopen("descompressed", "wb");

  	while((tam_lido = fread(buffer, 1, BUFFER_SIZE,file)) >= 1)
	{
		for (i = 0; i < tam_lido; ++i)
		{
			int evitar_lixo = 8;//valor que deverá ser usado onde não tiver lixo
			if ((tam_lido != BUFFER_SIZE) && ( i + 1 ==  tam_lido))
			{
				evitar_lixo = (8 - tam_lixo);
			}
			for (j = 0; j < evitar_lixo; ++j)
			{
				if (is_bit_set(&buffer[i], j))
				{
					arvore = arvore->right;
				}
				else
				{
					arvore = arvore->left;
				}
				if (arvore->right == NULL && arvore->left == NULL)
				{
					fputc(arvore->item, descompactado);
					arvore = raiz;
				}
			}
		}
	}
}
