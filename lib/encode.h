#ifndef ENCODE_H
#define ENCODE_H
#include <string.h>
#include <math.h>
#include "heap.h"
#include "bitmask.h"

/*
  Cria o tipo abstrato 'encode' onde a struct contém um buffer com os bytes do arquivo que será comprimido,
  o tamanho do arquivo (em bytes) e a contagem da frequência dos bytes.
*/
typedef struct encode
{
  unsigned char* buffer;
  int size;
  int frequency[256];
} encode;

/*
  Cria um novo 'encode', criando um buffer nulo, zerando a frequência dos bytes e o tamanho do arquivo.
  Retorna um ponteiro para o novo encode.
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
  Mapeia a nova representação de um byte do arquivo, usando a árvore de huffman.
*/
void trace_path(huffman_tree* root, huffman_tree* first,int item, int position, int* bpb, unsigned char* buffer);

/*
  Usando trace_path, mapeia a nova representação de todos os bytes do arquivo.
*/
void byte_maping(int* freq, huffman_tree* root, int* bpb, unsigned char** buffer);

/*
  Retorna a quantidade final de bits que o arquivo-saída deve possuir.
*/
int sum(int* bpb, int* freq);

/*
  Gera o cabeçalho do arquivo-final comprimido.
*/
unsigned char* make_header(int trash, int size_nodes, unsigned char* nodes);

/*
  Gera o arquivo-final comprimido.
*/
void create_final_file(int ffs,encode* archive,unsigned char* header,int sn,unsigned char** map,int* bpb);

#endif
