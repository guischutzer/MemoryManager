/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#define TRUE	1
#define FALSE	0
#define MAXCHAR 100

#include <stdlib.h>
#include <string.h>

typedef struct acesso Acesso;
struct acesso
{
  int     inst;
  int     pos;
  Acesso *prox;
};

typedef struct processo Processo;
struct processo
{
  char    nome[MAXCHAR];
  int     t0;
  int     tf;
  int     b;
  int     init;
  Acesso *head;
};

typedef struct node Node;
struct node
{
  char      tipo;
  int       inicio;
  int       tamanho;
  Node     *prox;
  Node     *quickprox;
};

typedef struct page Page;
struct page
{
  int   pid;
  int   pos;
  int   map;
  int   R;
};

typedef struct fifoPage FifoPage;
struct fifoPage{
  int       pag;
  FifoPage *prox;
};

char** tokenize(char* str);
