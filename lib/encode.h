#ifndef ENCODE_H
#define ENCODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Cria o tipo abstrato 'encode' onde a struct contém um buffer com os bytes do arquivo que será comprimido,
  o tamanho do arquivo (em bytes), a contagem da frequência dos bytes e a representação dos bytes após o huffman.
*/
typedef struct encode
{
  unsigned char* buffer;
  unsigned char bits_map[256];
  int frequency[256];
  int size;
} encode;

/*
  Cria um novo 'encode', criando um buffer nulo, zerando a frequência dos bytes e a representação dos bytes após o huffman.
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
  Mapeia uma árvore de Huffman, salvando a nova representação de cada byte após o huffman.
*/
void map_bytes(encode* archive, huffman_tree* root);

#endif
