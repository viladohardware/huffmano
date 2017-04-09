#include "../lib/encode.h"

encode* new_encode()
{
  int i;
  encode* new = (encode*) malloc(sizeof(encode));

  new->buffer = NULL;
  new->size = 0;
  memset(new->frequency,0,sizeof(int)*256);
  return new;
}

void picking_bytes(encode* archive, FILE* file)
{
  int buffer_size;

  fseek(file,0,SEEK_END);
  archive->size = ftell(file);
  rewind(file);

  archive->buffer = (unsigned char*) malloc(archive->size * sizeof(unsigned char));
  buffer_size = fread(archive->buffer,1,archive->size,file);

  if(buffer_size != archive->size) archive->buffer = NULL;
}

void count_frequency(encode* archive)
{
  int i;
  for(i = 0; i < archive->size; i++) archive->frequency[archive->buffer[i]]++;
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

void trace_path(int item, huffman_tree* root, int bpb, unsigned char* buffer, int buffer_size, int position)
{
  static int path_found = 0;
  if(root == NULL) return;

  if(root->item == item && (root->left == NULL && root->right == NULL))
  {
    path_found = 1;
    return;
  }
  else
  {
    bpb++;
    trace_path(item,root->left,bpb,buffer,buffer_size,position+1);
    if(path_found)
    {
      path_found = 0;
      return;
    }
    else
    {
      set_bit(buffer,position,buffer_size);
      trace_path(item,root->right,bpb,buffer,buffer_size,position+1);
      if(path_found)
      {
        path_found = 0;
        return;
      }
      else
      {
        unset_bit(buffer,position,buffer_size);
        bpb--;
        return;
      }
    }
  }
}

void byte_maping(int* freq, huffman_tree* root, int* bpb, unsigned char** buffer, int buffer_size)
{
  int i;

  for(i = 0; i < 256; i++)
  {
    if(freq[i] != 0)
    {
      trace_path(i,root,bpb[i],buffer[i],buffer_size,0);
    }
  }
}
