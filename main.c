#include "lib/encode.h"

#define MAX 8192

int main(void)
{
  char* url = (char*) malloc(sizeof(char) * MAX);
  FILE* file = NULL;
  encode* encode = new_encode();
  huffman_tree* root = NULL;
  int read = 0;

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
  file = NULL;

  printf("2 - Contando frequência dos bytes...\n");
  count_frequency(encode);
  printf("Frequência contada com sucesso.\n\n");

  printf("3 - Montando árvore de compressão...\n");
  root = build_huffman_tree(encode->frequency);
  printf("Árvore de compressão montada com sucesso.\n\n");

  printf("4 - Mapeando novos bits do arquivo...\n");
  //byte_maping(encode,root); fazendo

  return 0;
}
