#ifndef ENCODE_H
#define ENCODE_H
#include <string.h>
#include <math.h>
#include "heap.h"
#include "bitmask.h"

/*
  Cria o tipo abstrato 'encode' onde a struct contém um buffer com os bytes do arquivo que será comprimido,
  o tamanho do arquivo (em bytes), a contagem da frequência dos bytes, a representação dos bytes após o huffman e a
  quantidade de bits para cada representação.
*/
typedef struct encode
{
  unsigned char* buffer;
  int size;
  int frequency[256];
  unsigned char* byte_maping;
  int byte_size[256];
} encode;

/*
  Cria um novo 'encode', criando um buffer nulo, zerando a frequência dos bytes, a representação dos bytes após o huffman e a
  quantidade de bits para cada representação. Retorna um ponteiro para o novo encode.
*/
encode* new_encode();

/*
  Lê um arquivo e armazena todos os seus bytes em um buffer na struct 'encode'.
*/
void picking_bytes(encode* archive, FILE* file);

/*
  Conta a frequência dos bytes no buffer.
*/
void count_frequency(encode* archive);

/*
	Recebe um array de inteiros com a frequência de todos os caracteres da entrada, e retorna a árvore de huffman montada.
  Utiliza uma min_heap para a montagem.
*/
huffman_tree* build_huffman_tree(int* freq);

/*
  Mapeia uma árvore de Huffman, salvando a nova representação de cada byte após o huffman.
*/
void byte_maping(encode* archive, huffman_tree* root);

/*
Mapeia a nova representação de todos os bytes do arquivo, usando a árvore de huffman.
*/
void trace_huffman_path(encode* archive, int item, huffman_tree* root);

#endif
