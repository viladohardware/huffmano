#include "lib/encode.h"

#define MAX 8192

int main(void)
{
  unsigned char* nodes = (char*) malloc(sizeof(unsigned char) * MAX);
  char* url = (char*) malloc(sizeof(char) * 1000);
  FILE* file = NULL;
  encode* encode = new_encode();
  huffman_tree* root = NULL;
  int read = 0, i;

  while(!read)
  {
    printf("Digite o caminho do arquivo:\n");
    scanf("%s",url);
    getchar();

    file = fopen(url,"rb");
    if(file != NULL)
    {
      printf("Arquivo carregado com sucesso.\n\n");
      read = 1;
    }
    else printf("Falha ao carregar o arquivo, tente novamente.\n\n");
  }

  printf("1 - Acessando bytes do arquivo...\n");
  picking_bytes(encode,file);
  if(encode->buffer != NULL) printf("Bytes acessados com sucesso.\n\n");
  else
  {
    printf("Falha ao acessar os bytes do arquivo.\n\n");
    return 0;
  }

  fclose(file);
  free(url);
  url = NULL;
  file = NULL;

  printf("2 - Contando frequência dos bytes...\n");
  count_frequency(encode);
  printf("Frequência contada com sucesso.\n\n");

  printf("3 - Montando árvore de compressão...\n");
  root = build_huffman_tree(encode->frequency);
  printf("Árvore de compressão montada com sucesso.\n\n");

  printf("4 - Mapeando novos bits do arquivo...\n");
  int bits_per_byte[256];
  memset(bits_per_byte,0,sizeof(int)*256);

  int max_bits = height(root);
  int map_size = (int) ceil(max_bits/8.0);

  unsigned char* map[256];
  for(i = 0; i < 256; i++)
  {
    map[i] = (unsigned char*) malloc(sizeof(unsigned char) * map_size);
    memset(map[i],0,sizeof(unsigned char)*map_size);
  }

  byte_maping(encode->frequency,root,bits_per_byte,map,map_size);
  printf("Mapeamento feito com sucesso.\n\n");

  printf("5 - Gerando cabeçalho...\n");
  int trash = sum(bits_per_byte,encode->frequency) % 8;
  int* size_nodes = (int*) malloc(sizeof(int));
  (*size_nodes) = 0;

  save_pre_order(root,nodes,size_nodes);
  //unsigned char* header = header();
  //free(nodes);
  //nodes = NULL;

  return 0;
}
