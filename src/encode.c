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
  int teste = 0;
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
      teste++;
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

void trace_path(huffman_tree* root, huffman_tree* first,int item, int position, int* bpb, unsigned char* buffer)
{
  static int found = 0;
  if(root == NULL) return;

  if(root->item == item && root->left == NULL && root->right == NULL)
  {
    found = 1;
    return;
  }
  else
  {
    bpb[item]++;
    trace_path(root->left,first,item,position+1,bpb,buffer);

    if(!found)
    {
      set_bit(buffer,position);
      trace_path(root->right,first,item,position+1,bpb,buffer);
    }
    if(!found)
    {
      unset_bit(buffer,position);
      bpb[item]--;
    }
  }

  if(root == first && found) found = 0;
}

void byte_maping(int* freq, huffman_tree* root, int* bpb, unsigned char** buffer)
{
  int i;

  for(i = 0; i < 256; i++)
  {
    if(freq[i] != 0) trace_path(root,root,i,0,bpb,buffer[i]);
  }
}

int sum(int* bpb, int* freq)
{
  int i;
  int sum = 0;

  for(i = 0; i < 256; i++)
  {
    if(freq[i] != 0) sum += bpb[i] * freq[i];
  }
  return sum;
}

void create_final_file(int ffs,encode* archive,unsigned char* header,int sn,unsigned char** map,int* bpb)
{
  int i, j;
  int position = 0;

  FILE* file = fopen("../../compressed.huff","wb");
  unsigned char* aux;

  unsigned char* final_file = (unsigned char*) malloc(sizeof(unsigned char) * (ffs-sn-2));
  memset(final_file,0,sizeof(unsigned char) * (ffs-sn-2));

  for(i = 0; i < archive->size; i++)
  {
      aux = map[archive->buffer[i]];
      for(j = 0; j < bpb[archive->buffer[i]]; j++)
      {
        if(is_bit_set(aux,j)) set_bit(final_file,position);
        position++;
      }
  }
  fwrite(header , sizeof(unsigned char), sn+2, file);
  fwrite(final_file , sizeof(unsigned char), ffs-sn-2, file);
  fclose(file);
}
