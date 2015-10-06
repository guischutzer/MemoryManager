/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#ifndef _UTILS_H
#define _UTILS_H

#define TRUE	1
#define FALSE	0
#define MAXCHAR 100
#define MAXPROCESSOS 20

#include <stdlib.h>
#include <string.h>

typedef struct node Node;
struct node
{
  char   tipo;
  int    inicio;
  int    tamanho;
  Node*  prox;
};

typedef struct acesso Acesso;
struct acesso
{
  int     inst;
  int     pos;
  Acesso* prox;
};

typedef struct processo Processo;
struct processo
{
  char    nome[MAXCHAR];
  int     t0;
  int     tf;
  int     b;
  Acesso* head;
};

char** tokenize(char* str);

#endif
