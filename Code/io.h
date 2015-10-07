

#ifndef _IO_H
#define _IO_H

Processo inputProcesso(char* linha);

void criabin(int t, FILE *arquivo);

int carrega(char* nome, int* total, int* virtual, Processo* lista_proc);

void liberaListaAcessos(Acesso *head);

void liberaListaProcessos(Processo *lista_proc, int tamanho);

#endif
