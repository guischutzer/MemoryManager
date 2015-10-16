
/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomas Marcondes Bezerra Paim - 7157602

*/

#include <stdio.h>
#include "utils.h"
#include "io.h"

void imprimeNode(Node* head) {
	Node* aux = NULL;
	aux = head;
  printf("[             HEAD---]\n");
	while (aux != NULL){
		printf("[--->[%c|%4d|%4d]---]\n", aux->tipo, aux->inicio*16, aux->tamanho*16);
		aux = aux->prox;
	}
  printf("[--->NULL            ]\n");
}

void imprimeBin(FILE* arquivo, int tamanho) {
	int i, pag = 0;
	char c;
	for (i = 1; i <= tamanho; i++) {
			fseek(arquivo, sizeof(char)*i-1,SEEK_SET);
			fread(&c, sizeof(char), 1, arquivo);
			if(i%16 == 1){
				printf("pag %02d:  [", pag++);
			}
			printf("%4d", c);
      if (i%16 == 0)
        printf("   ]\n");
	}
	printf ("\n");
}

void escreveBin(char pid, FILE* arquivo, int origem, int pags){
	int i;

	fseek(arquivo, sizeof(char)*origem*16, SEEK_SET);

	for(i = 0; i < pags*16; i++)
		fwrite(&pid, sizeof(pid), 1, arquivo);
}

void imprimePags(Page* lista, int tamanho){
  int i;
  printf("NO. PAG  [PID|POS|MAP|  R]\n");
  printf("----------------------\n");
  for(i = 0; i < tamanho; i++){
    printf("pag %02d   [%3d|%3d|%3d|%3d]\n", i, lista[i].pid, lista[i].pos, lista[i].map, lista[i].R);
  }
  printf("\n");
}

void imprimeFrames(int* lista, int tamanho){
  int i;
  printf("         USADO      \n");
  printf("------------------\n");
  for(i = 0; i < tamanho; i++){
    if(lista[i]) printf("fra %02d [#######]\n", i);
    else printf("fra %02d [       ]\n", i);
  }
  printf("\n");
}

Processo inputProcesso(char* linha) {
  int       i;
  char**    tokens = NULL;
  Processo  p;
  Acesso   *a;


  tokens = tokenize(linha);

  strcpy(p.nome, tokens[1]);
  p.t0    = atoi(tokens[0]);
  p.tf    = atoi(tokens[2]);
  p.b     = atoi(tokens[3])/16;
  p.init  = -1;
  if(atoi(tokens[3]) % 16 != 0)
    p.b++;

  p.head = NULL;

  if(tokens[4] != NULL) {
    a = malloc(sizeof(Acesso));
    a->pos = atoi(tokens[4])/16;
    a->inst = atoi(tokens[5]);
    p.head = a;

    for(i = 6; tokens[i] != NULL; i++){
      a->prox = malloc(sizeof(Acesso));
      a->prox->pos = atoi(tokens[i])/16;
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
  Acesso *a = NULL;
  printf("Processo %s\n", proc.nome);
  printf("Tempo de inicio e fim: %d, %d.\n", proc.t0, proc.tf);
  printf("Tamanho do processo: %d bytes.\n", proc.b);
  a = proc.head;
  while(a != NULL){
    printf("Acesso a posicao %d no instante %d.\n", a->pos, a->inst);
    a = a->prox;
  }
}

Processo* carrega(char* nome, int* total, int* virtual, int* nproc) {

  FILE     *a = NULL, *b = NULL;
  char     linha[MAXCHAR];
  int      i, nprocloc;
  char   **tokens = NULL;
  Processo* lista_proc = NULL;

  a = fopen(nome, "r");
  if (a == NULL){
    printf("ERRO: arquivo %s nao encontrado.\n", nome);
    return NULL;
  }
  b = fopen(nome, "r");
  if (b == NULL){
    printf("ERRO: arquivo %s nao encontrado.\n", nome);
    return NULL;
  }

  fgets(linha, MAXCHAR, a);
  fgets(linha, MAXCHAR, b);
  tokens = tokenize(linha);
  *total = atoi(tokens[0])/16;
  *virtual = atoi(tokens[1])/16;
  if (tokens != NULL)
    free(tokens);

  for(nprocloc = 0; fgets(linha, MAXCHAR, a); nprocloc++);

  lista_proc = malloc(nprocloc * sizeof(Processo));
  if(lista_proc == NULL)
    printf("Falha ao alocar lista_proc.\n");

  for(i = 0; fgets(linha, MAXCHAR, b); i++){
    (lista_proc[i]) = inputProcesso(linha);
  }

  *nproc = nprocloc;

  fclose(a);

  return lista_proc;
}

void liberaListaAcessos(Acesso *head){
  Acesso *morta = NULL;

  while(head != NULL){
    morta = head;
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
