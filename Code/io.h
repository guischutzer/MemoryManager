

#ifndef _IO_H
#define _IO_H

Processo inputProcesso(char* linha);

void criabin(int t, FILE *arquivo);

void imprimeProc (Processo proc);

Processo* carrega(char* nome, int* total, int* virtual, int* nproc);

void liberaListaAcessos(Acesso *head);

void liberaListaProcessos(Processo *lista_proc, int tamanho);

#endif
