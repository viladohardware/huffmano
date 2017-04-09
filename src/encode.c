#include "../lib/encode.h"

encode* new_encode()
{
  int i;
  encode* new = (encode*) malloc(sizeof(encode));

  new->buffer = NULL;
  new->size = 0;
  memset(new->frequency,0,sizeof(int)*256);
  memset(new->bits_map,0,sizeof(unsigned char)*256);
  return new;
}

void picking_bytes(encode* archive, FILE* file)
{
  int buffer_size;

  fseek(file,0,SEEK_END);
  archive->size = ftell(file);
  rewind(file);

  buffer_size = fread(archive->buffer,1,archive->size,file);

  if(buffer_size != archive->size) archive->buffer = NULL;
}

void count_frequency(encode* archive)
{
  int i;
  for(i = 0; i < archive->size; i++) archive->frequency[archive->buffer[i]]++;
}
