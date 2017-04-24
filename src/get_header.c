#include "../lib/get_header.h"

void open(FILE* file)
{
	if (file == NULL) printf("O arquivo não pode ser aberto\n");
	else printf("O arquivo foi aberto\n");
}

int trash(FILE* file)
{
	int trash_size = 0, i;
	unsigned char aux_trash;

	fscanf(file, "%c", &aux_trash);

	for (i = 7; i >= 5; --i)
	{
		if ((aux_trash & (1 << i))) trash_size += pow(2, (i - 5));
	}

	rewind(file);
	return trash_size;
}

int tree_size(FILE* file)
{
	int size = 0, i, max = 12;
	unsigned char aux_size1;
	unsigned char aux_size2;

	fscanf(file, "%c%c", &aux_size1, &aux_size2);

	for (i = 4; i >= 0 ; --i)
	{
		if ((aux_size1 & (1 << i))) size += pow(2, max);
		max--;
	}

	for (i = 7; i >= 0 ; --i)
	{
		if ((aux_size2 & (1 << i))) size += pow(2, max);
		max--;
	}

	return size;
}

unsigned char* pre_order_tree(FILE* file, int tree_size)
{
	int i;
	unsigned char* tree = malloc(tree_size * sizeof(unsigned char));

	for (i = 0; i < tree_size; ++i)
	{
		fscanf(file, "%c", &tree[i]);
	}

	return tree;
}
