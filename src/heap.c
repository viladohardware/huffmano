#include "../lib/huffman_tree.h"
#include "../lib/heap.h"

heap* create_heap()
{
	int i;
	heap* new_heap = (heap*) malloc(sizeof(heap));
	new_heap->size = 0;
	for(i = 1; i <= MAX_SIZE; i++)
	{
		new_heap->node[i] = NULL;
	}
	return new_heap;
}

int get_parent_index(heap* heap, int index)
{
	return index >> 1;
}

int get_left_index(heap* heap, int index)
{
	return index << 1; 
}

int get_right_index(heap* heap, int index)
{
	return (index<<1)+1; 
}

void swap(huffman_tree* a, huffman_tree* b)
{
	huffman_tree aux;
	aux = *a;
	*a   = *b;
	*b   = aux;
}

void min_heapify(heap *heap, int index)
{
	int lowest;																		
	int left_index  = get_left_index (heap ,index);
	int right_index = get_right_index(heap, index);

	if(left_index <= heap->size && heap->node[left_index]->frequency < heap->node[index]->frequency)
	{
		lowest = left_index;
	}
	else
	{
		lowest = index;
	}
	if(right_index <= heap->size && heap->node[right_index]->frequency < heap->node[lowest]->frequency)
	{
		lowest = right_index;
	}
	if(heap->node[index]->frequency != heap->node[lowest]->frequency)
	{
		swap(heap->node[index], heap->node[lowest]);
		min_heapify(heap, lowest);
	}
}

void enqueue(heap *heap, huffman_tree* leaf)
{
	if(heap->size >= MAX_SIZE)
	{
		printf("Heap overflow\n");
	}
	else
	{
		heap->node[++heap->size] = leaf;
		
		int key_index = heap->size;
		int parent_index = get_parent_index(heap, heap->size);

		while(parent_index >= 1 && heap->node[key_index]->frequency < heap->node[parent_index]->frequency )	
		{
			swap(heap->node[key_index], heap->node[parent_index]);
		
			key_index = parent_index;

			parent_index = get_parent_index(heap, key_index);
		}
	}
}

int is_empty(heap *heap)
{
	if(heap->size == 0)
	{
		return 1;
	}
	return 0;
}

huffman_tree* dequeue(heap* heap)
{
	if(is_empty(heap))
	{
		printf("Heap underflow\n");
	}
	else
	{
		huffman_tree* item = heap->node[1];
		heap->node[1] = heap->node[heap->size];
		heap->size--;
		min_heapify(heap, 1);
		return item;		
	}
}
void print_heap(heap* heap)
{
	int i;
	for(i = 1; i <= heap->size; i++)
	{
		if(heap->size != i) printf("%c: %d ", heap->node[i]->item, heap->node[i]->frequency);
		else printf("%c: %d\n", heap->node[i]->item, heap->node[i]->frequency);
	}
}

huffman_tree* build_huffman_tree(int* freq)
{
	int i;
	huffman_tree* leaf;
	huffman_tree* root;
	huffman_tree* right;
	huffman_tree* left;
	huffman_tree* parent;

	heap* heap = create_heap();

	for(i = 0; i < 256; i++)
	{
		if(freq[i] != 0)
		{
			leaf = create_leaf(i, freq[i]);
			enqueue(heap, leaf);
		}
	}
	while(heap->size > 1 )
	{
		left   = dequeue(heap);
		right  = dequeue(heap);
		parent = create_parent(left, right);
		enqueue(heap, parent);
	}
	root = dequeue(heap);
	return root;
}