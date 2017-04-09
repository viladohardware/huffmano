#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char set_bit (unsigned char c, int i)
{
	unsigned char mask = 1<<i;
	return mask|c ;
}

unsigned char* cabecalho(int trash, int size, unsigned char *array)
{
	int i=5, j=0, k=1;
	unsigned char tree[size+2];
	memset(tree, 0, (size + 2)*sizeof(unsigned char));

	while(trash != 0)
	{
		if(trash & 1)
		{
			set_bit(tree[0], i);
		}
		trash = trash>>1;
		++i;
	}

	while(size != 0)
	{
		if(j==8)
		{
			j = 0;
			k = 0;
		}
		if(size & 1)
		{
			set_bit(tree[k], j);
		}
		size = size>>1;
		++j;
	}

	for(i=0; i<size; ++i)
	{
		tree[i+2] = array[i];
	}

	return tree;
}
