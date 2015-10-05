
/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#include <stdio.h>
#include "utils.h"

Processo inputProcesso(char* linha) {
  int       i;
  char**    tokens;
  Processo p;
  Acesso   *a;

  tokens = tokenize(linha);

  strcpy(p.nome, tokens[1]);
  p.t0    = atoi(tokens[0]);
  p.tf    = atoi(tokens[2]);
  p.b     = atoi(tokens[3]);

  if(tokens[4] != NULL) {
    a = malloc(sizeof(Acesso));
    a->pos = atoi(tokens[4]);
    a->inst = atoi(tokens[5]);
    p.head = a;

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


int main(int argc, char const *argv[]) {

  FILE     *entrada;
  char     linha[MAXCHAR];
  int      i, j, nproc = 0;
  int      total, virtual;
  char   **tokens;
  Processo lista_proc[MAXPROCESSOS];

  entrada = fopen(argv[1], "r");

  fgets(linha, MAXCHAR, entrada);
  tokens = tokenize(linha);
  total = atoi(tokens[0]);
  virtual = atoi(tokens[1]);

  for(i = 0; fgets(linha, MAXCHAR, entrada); i++){
    lista_proc[i] = inputProcesso(linha);
    nproc++;
  }

  return 0;
}
