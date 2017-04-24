#include "../lib/rebuild_tree.h"

binary_tree* create_empty_binary_tree()
{
	return NULL;
}

int is_empty_tree(binary_tree* bt)
{
	if (bt == NULL) return 1;
	return 0;
}

void print_pre_order (binary_tree* bt)
{
	if (!is_empty(bt))
	{
		printf("%c\n", bt->item);
		print_pre_order(bt->left);
		print_pre_order(bt->right);
	}
}

binary_tree* rebuild_tree(binary_tree* ht, unsigned char* key, int nivel)
{
	static int indice = 0;
	if(key[indice] == '*')
	{
		ht = malloc(sizeof(binary_tree));
		ht->item = key[indice];
		++indice;
		ht->left = rebuild_tree(ht->left, key, nivel + 1);
		ht->right = rebuild_tree(ht->right, key, nivel + 1);
	}
	else if(key[indice] == '\\')
	{
		++indice;
		ht = malloc(sizeof(binary_tree));
		ht->item = key[indice];
		ht->left = NULL;
		ht->right = NULL;
		++indice;
	}
	 else
	{
		ht = malloc(sizeof(binary_tree));
		ht->item = key[indice];
		ht->left = NULL;
		ht->right = NULL;
		++indice;
	}
	if(nivel == 0)
	{
		indice = 0;
	}
	return ht;
}
