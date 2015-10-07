
/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#include <stdio.h>
#include "utils.h"
#include "io.h"

void criabin(int t, FILE *arquivo)
  {
    int i;
    char c = -1;
    for (i = 0; i < t; i++){
      fwrite(&c, sizeof(char), 1, arquivo);
    }
  }

Processo inputProcesso(char* linha) {
  int       i;
  char**    tokens = NULL;
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

  if(tokens != NULL)
    free(tokens);

  return p;
}

void imprimeProc (Processo proc){
  Acesso *acc = NULL;
  printf("Processo %s\n", proc.nome);
  printf("Tempo de inicio e fim: %d, %d.\n", proc.t0, proc.tf);
  printf("Tamanho do processo: %d bytes.\n", proc.b);
  acc = proc.head;
  while(acc != NULL){
    printf("Acesso a posicao %d no instante %d.\n", acc->pos, acc->inst);
    acc = acc->prox;
  }
}

int carrega(char* nome, int* total, int* virtual, Processo* lista_proc) {

  FILE     *a = NULL, *b = NULL;
  char     linha[MAXCHAR];
  int      nproc, i;
  char   **tokens = NULL;

  a = fopen(nome, "r");
  if (a == NULL){
    printf("ERRO: arquivo %s não encontrado.\n", nome);
    return 1;
  }
  b = fopen(nome, "r");
  if (b == NULL){
    printf("ERRO: arquivo %s não encontrado.\n", nome);
    return 1;
  }

  fgets(linha, MAXCHAR, a);
  fgets(linha, MAXCHAR, b);
  tokens = tokenize(linha);
  *total = atoi(tokens[0]);
  *virtual = atoi(tokens[1]);
  if (tokens != NULL)
    free(tokens);

  for(nproc = 0; fgets(linha, MAXCHAR, a); nproc++);
  lista_proc = malloc(sizeof(Processo) * nproc);

  for(i = 0; fgets(linha, MAXCHAR, b); i++)
    lista_proc[i] = inputProcesso(linha);

  fclose(a);

  for (i = 0; i < nproc; i++)
    imprimeProc(lista_proc[i]);

  return nproc;
}

void liberaListaAcessos(Acesso *head){
  Acesso *morta = NULL;

  morta = head;
  while(head != NULL){
    head = head->prox;

    free(morta);
    morta = NULL;
  }
}

void liberaListaProcessos(Processo* lista_proc, int tamanho){
  int i;

  for(i = 0; i < tamanho; i++)
    liberaListaAcessos(lista_proc[i].head);

  free(lista_proc);
  lista_proc = NULL;
}
