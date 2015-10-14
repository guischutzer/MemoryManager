/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "utils.h"
#include "io.h"

int checaQuadro(FILE *arquivo, Page *head, int pos, int pid){
  Page *p;

  for(p = head; p != NULL; p++){
    if(p->pos == pos && p->pid == pid)
      return p->map;
  }

  return -1;
}

Page* criaPaginas(Processo *lista_proc, int index){
  Page *p, *head;
  int i;

  p = malloc(sizeof(Page));
  p->pid = index;
  p->map = -1;
  p->prox = NULL;
  head = p;

  for(i = 1; i < lista_proc[index].b; i++){
    p->prox = malloc(sizeof(Page));
    p->prox->pid = index;
    p->prox->map = -1;
    p->prox->prox = NULL;
    p = p->prox;
  }

  return head;
}

void NRUP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}

void FIFO(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}

void SCP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}

void LRUP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}
