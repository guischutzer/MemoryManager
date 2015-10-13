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
#include "fit.h"
#include "io.h"

void mergeNode(Node* head){
	Node* aux = NULL;
	Node* morta = NULL;
	aux = head;
	while (aux != NULL){
		while ((aux->tipo == 'L') && (aux->prox != NULL) && (aux->prox->tipo == 'L')){
			aux->tamanho = (aux->tamanho + aux->prox->tamanho);
			morta = aux->prox;
			aux->prox = aux->prox->prox;
			free(morta);
		}
		aux = aux->prox;
	}
	return;
}

int firstFit(FILE* arquivo, int pid, int tamanho, Node *lista){

	Node *newNode, *aux;
	int encontrou = FALSE;
	int origem;

	aux = lista;

	while (aux != NULL){
		if ((aux->tipo == 'L') && (aux->tamanho >= tamanho)){
			encontrou = TRUE;
			newNode = NULL;
			origem = aux->inicio;
			if (aux->tamanho > tamanho){
				newNode = malloc(sizeof(Node)); /* cria um novo no caso tenha sobrado memoria livre no no atual */
				newNode->tipo = 'L';
				newNode->prox = aux->prox;
				newNode->inicio = (aux->inicio + tamanho);
				newNode->tamanho = (aux->tamanho - tamanho);

				aux->prox = newNode;
				aux->tamanho = tamanho;
				aux->tipo = 'P';

			}
			else {
				aux->tipo = 'P';
			}

			escreveBin(pid, arquivo, aux->inicio, tamanho);
		}
		if (encontrou == TRUE)
			break;
		else
			aux = aux->prox;
	}


	if (encontrou == FALSE)
		printf("ERRO: Memoria insuficiente.\n");

	return aux->inicio;
}

int nextFit(FILE* arquivo, int pid, int tamanho, Node* lista){
	return 0;
}

int quickFit(FILE* arquivo, int pid, int tamanho, Node* lista){
	return 0;
}
