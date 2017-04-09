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


void print_pre_order (huffman_tree* huffman)
{
	if (huffman != NULL)
	{
		printf("%c\n", huffman->item);
		print_pre_order(huffman->left);
		print_pre_order(huffman->right);
	}
}
