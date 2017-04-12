#include "lib/encode.h"
#define MAX 8192

void encoding(FILE* file)
{
  int i;
  printf("1 - Acessando bytes do arquivo...\n");
  encode* encode = new_encode();
  picking_bytes(encode,file);
  if(encode->buffer != NULL) printf("Bytes acessados com sucesso.\n\n");
  else
  {
    printf("Falha ao acessar os bytes do arquivo.\n\n");
    return 0;
  }

  fclose(file);
  file = NULL;

  printf("2 - Contando frequência dos bytes...\n");
  count_frequency(encode);
  printf("Frequência contada com sucesso.\n\n");

  printf("3 - Montando árvore de compressão...\n");
  huffman_tree* root = NULL;
  root = build_huffman_tree(encode->frequency);
  printf("Árvore de compressão montada com sucesso.\n\n");

  printf("4 - Mapeando novos bits do arquivo...\n");
  int bits_per_byte[256];
  memset(bits_per_byte,0,sizeof(int)*256);

  int max_bits = height(root);
  int map_size = (int) ceil(max_bits/8.0);

  unsigned char** map = malloc(sizeof(unsigned char*) * 256);
  for(i = 0; i < 256; i++)
  {
    map[i] = malloc(sizeof(unsigned char) * map_size);
    memset(map[i],0,sizeof(unsigned char) * map_size);
  }

  byte_maping(encode->frequency,root,bits_per_byte,map);
  printf("Mapeamento feito com sucesso.\n\n");

  printf("5 - Gerando cabeçalho...\n");
  unsigned char nodes[MAX];
  int trash = 8 - (sum(bits_per_byte,encode->frequency) % 8);
  int size_nodes;
  size_nodes = 0;

  save_pre_order(root,nodes,&size_nodes);

  unsigned char* header;

  header = make_header(trash,size_nodes,nodes);
  printf("Cabeçalho feito com sucesso.\n\n");

  printf("6 - gerando arquivo-saída...\n");
  int final_file_size = (int) ceil(sum(bits_per_byte,encode->frequency)/8.0) + size_nodes + 2;
  create_final_file(final_file_size,encode,header,size_nodes,map,bits_per_byte);
  printf("Arquivo comprimido gerado com sucesso.\n\n");
  return;
}

void decoding(FILE* file)
{
  return;
}

int main(void)
{
  int read = 0;
  char* url = (char*) malloc(sizeof(char) * 1000);
  char  ans;
  char* mode;

  FILE* file = NULL;

  while(!read)
  {
    printf("Digite o caminho do arquivo:\n");
    scanf("%s",url);
    getchar();

    file = fopen(url,"rb");
    if(file != NULL)
    {
      printf("Arquivo carregado com sucesso.\n\n");

      mode = strstr(url,".huff");
      if(mode == NULL) encoding(file);
      else decoding(file);
      file = NULL;

      printf("Deseja fazer mais alguma operação? (S/N)\n");
      scanf("%c",&ans);
      getchar();
      printf("\n\n");

      if(ans == 'N') read = 1;
      else if(ans != 'S')
      {
        printf("Comando não reconhecido. Encerrando a aplicação.\n\n");
        read = 1;
      }
    }
    else printf("Falha ao carregar o arquivo, tente novamente.\n\n");
  }

  return 0;
}
