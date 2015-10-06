
/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#include <stdio.h>
#include "utils.h"
#include "io.h"

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


int carrega(char* nome, int* total, int* virtual, Processo* lista_proc) {

  FILE     *entrada;
  char     linha[MAXCHAR];
  int      nproc;
  char   **tokens;

  entrada = fopen(nome, "r");

  fgets(linha, MAXCHAR, entrada);
  tokens = tokenize(linha);
  *total = atoi(tokens[0]);
  *virtual = atoi(tokens[1]);
  free(tokens);

  for(nproc = 0; fgets(linha, MAXCHAR, entrada); nproc++)
    lista_proc[nproc] = inputProcesso(linha);

  fclose(entrada);

  return nproc;
}
