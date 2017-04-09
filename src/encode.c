#include "../lib/encode.h"

encode* new_encode()
{
  int i;
  encode* new = (encode*) malloc(sizeof(encode));

  new->buffer = NULL;
  new->byte_maping = NULL;
  new->size = 0;
  memset(new->frequency,0,sizeof(int)*256);
  memset(new->byte_size,0,sizeof(int)*256);
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

void byte_maping(encode* archive, huffman_tree* root)
{
  int i;
  int tree_height = height(root);
  float bits_per_byte = (float) tree_height/8;
  int numberof_bytes = ceil(bits_per_byte);

  archive->byte_maping = (unsigned char*) malloc(256 * (sizeof(unsigned char) * numberof_bytes));

  for(i = 0; i < 256; i++)
  {
    if(archive->frequency[i] != 0)
    {
      trace_huffman_path(archive,i,root,-1);
    }
  }
}

void trace_huffman_path(encode* archive, int item, huffman_tree* root,int position)
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
    archive->byte_size[item]++;
    trace_huffman_path(archive,item,root->left,position+1);
    if(path_found) return;
    else
    {
      //seta bit na posição atual
      trace_huffman_path(archive,item,root->right,position+1);
      if(path_found) return;
      else
      {
        //deixa bit no 0 novamente
        archive->byte_size[item]--;
        return;
      }
    }
  }
}
