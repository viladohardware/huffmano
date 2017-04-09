#include "../lib/huffman_tree.h"

huffman_tree* create_leaf(unsigned char item, int frequency)
{
	huffman_tree* new = (huffman_tree*) malloc(sizeof(huffman_tree));

	new->item = item;
	new->frequency = frequency;
	new->left = NULL;
	new->right = NULL;

	return new;
}

huffman_tree* create_parent(huffman_tree* left, huffman_tree* right)
{
	huffman_tree* new = (huffman_tree*) malloc(sizeof(huffman_tree));

	new->item = '*';
	new->frequency = left->frequency + right->frequency;
	new->left = left;
	new->right = right;

	return new;
}

huffman_tree* search(huffman_tree* huffman, unsigned char item)
{
	huffman_tree* result = NULL;

	if(huffman == NULL) return NULL;

	if(huffman->item == item) return huffman;
	else
	{
		if(huffman->left != NULL) result = search(huffman->left,item);
		if(result == NULL && huffman->right != NULL) result = search(huffman->right,item);
	}
	return result;
}


void save_pre_order (huffman_tree* huffman, unsigned char* string, int* position)
{
	if (huffman != NULL)
	{
		if(huffman->item == '*' || huffman->item == '\\')
		{
			if(huffman->left == NULL && huffman->right == NULL)
			{
				string[(*position)++] = '\\';
				string[(*position)++] = huffman->item;
			}
			else
			{
				string[(*position)++] = huffman->item;
			}
		}
		else
		{
			string[(*position)++] = huffman->item;
		}
		save_pre_order(huffman->left,string,position);
		save_pre_order(huffman->right,string,position);
	}
}

int max (int a, int b)
{
	return (a > b) ? a:b;
}

int height (huffman_tree* huffman)
{
	if (huffman == NULL) return -1;
	else return (1 + max(height(huffman->left), height(huffman->right)));
}
