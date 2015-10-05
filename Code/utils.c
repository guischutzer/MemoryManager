
/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

Processo inputline(char* linha) {
  int       i;
  char**    tokens;
  Processo *p;
  Acesso   *a;

  p = malloc(sizeof(Processo));
  tokens = tokenize(linha);

  strcpy(p->nome, tokens[1]);
  p->t0    = atoi(tokens[0]);
  p->tf    = atoi(tokens[2]);
  p->b     = atoi(tokens[3]);

  if(tokens[4] != NULL) {
    a = malloc(sizeof(Acesso));
    a->pos = atoi(tokens[4]);
    a->inst = atoi(tokens[5]);
    p->head = a;

    for(i = 6; tokens[i] != NULL; i++){
      a->prox = malloc(sizeof(Acesso));
      a->prox->pos = atoi(tokens[i]);
      a->prox->inst = atoi(tokens[++i]);
      a = a->prox;
    }

    a->prox = NULL;
  }

  free(tokens);

  return p;
}

char** tokenize(char* str) {
  char** tokens;
  int i;

  tokens = malloc(sizeof (char*) * MAXCHAR);
  tokens[0] = strtok(str, " ");

  for(i = 1; tokens[i - 1] != NULL; i++) {
    tokens[i] = strtok(NULL, " ");
  }

  return tokens;
}
