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

void trace_path(int item, huffman_tree* root, int* bpb, unsigned char* buffer, int buffer_size, int position)
{
  static int path_found = 0;
  static int count = 0;

  if(root == NULL) return;

  if(root->item == item && (root->left == NULL && root->right == NULL))
  {
    path_found = 1;
    int k;
    for(k = 0; k < count; k++)
    {
      printf("%d ",is_bit_set(buffer,k,buffer_size));
    }
    printf("\n");
    bpb[item] = count;
    count--;
    return;
  }
  else
  {
    count++;
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
        if(!path_found) unset_bit(buffer,position,buffer_size);
        count--;
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
      trace_path(i,root,bpb,buffer[i],buffer_size,0);
      printf("-----------------------------\n");
      int k;
      for(k = 0; k < bpb[i]; k++)
      {
        printf("%d ",is_bit_set(buffer[i],k,buffer_size));
      }
      printf("\n\n");
    }
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

void create_final_file(int ffs,encode* archive,unsigned char* header,int sn,unsigned char** map,int map_size,int* bpb)
{
  //FILE* file = fopen("compressed.huff","ab");
  //if(header != NULL) fwrite(header,1,sn+2,file);
  //else printf("fudeu :/\n");

  //unsigned char final_file[ffs-sn-2];
  //memset(final_file,0,sizeof(unsigned char)*(ffs-sn-2));

  //int position = 0;
  int i,j;

  for(j = 0; j < 8; j++)
  {
    printf("%d ",is_bit_set(map[65],j,map_size));
  }
  //for(i = 0; i < archive->size; i++)
  //{

  //}
  printf("\n");

  //fwrite(final_file,sizeof(unsigned char),sizeof(final_file),file);
  //fclose(file);
}
