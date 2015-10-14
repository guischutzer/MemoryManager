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

Node *nextNode = NULL;

void mergeNode(Node* head){
	Node* aux = NULL;
	Node* morta = NULL;
	aux = head;
	while (aux != NULL){
		while ((aux->tipo == 'L') && (aux->prox != NULL) && (aux->prox->tipo == 'L')){
			if (nextNode == aux->prox)
				nextNode = aux;
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

	aux = lista;

	while (aux != NULL){
		if ((aux->tipo == 'L') && (aux->tamanho >= tamanho)){
			encontrou = TRUE;
			newNode = NULL;

			if (aux->tamanho > tamanho){
				newNode = malloc(sizeof(Node)); /* cria um novo no caso tenha sobrado memoria livre no no atual */
				newNode->tipo = 'L';
				newNode->prox = aux->prox;
				newNode->inicio = (aux->inicio + tamanho);
				newNode->tamanho = (aux->tamanho - tamanho);
				newNode->quickprox = NULL;

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

int nextFit(FILE* arquivo, int pid, int tamanho, Node *lista){

	Node *newNode, *aux, *initNode = NULL;
	int encontrou = FALSE;

	if (nextNode != NULL)
		aux = nextNode;
	else aux = lista;

	while (aux != NULL){
		if ((aux->tipo == 'L') && (aux->tamanho >= tamanho)){
			encontrou = TRUE;
			newNode = NULL;

			if (aux->tamanho > tamanho){
				newNode = malloc(sizeof(Node)); /* cria um novo no caso tenha sobrado memoria livre no no atual */
				newNode->tipo = 'L';
				newNode->prox = aux->prox;
				newNode->inicio = (aux->inicio + tamanho);
				newNode->tamanho = (aux->tamanho - tamanho);
				newNode->quickprox = NULL;

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
		if ((aux == NULL) && (initNode == NULL)){
			aux = lista;
			initNode = nextNode;
		}
		if ((initNode != NULL) && (aux == initNode)){
			break;
		}
		nextNode = aux;
	}

	if (encontrou == FALSE)
		printf("ERRO: Memoria insuficiente.\n");

	return aux->inicio;
}

int quickFit(FILE* arquivo, int pid, int tamanho, Node **lista, int tam_max){
	Node *newNode, *aux;
	int encontrou = FALSE, i;

	i = tamanho-1;

	aux = lista[i];

	/* procura por um espaco com tamanho suficiente para o processo */
	while (aux == NULL){
		i++;
		if (i == tam_max){
			printf("ERRO: Memoria insuficiente.\n");
			return -1;
		}
		aux = lista[i];
	}

	lista[i] = lista[i]->quickprox;
	if (aux->tamanho > tamanho){
		newNode = malloc(sizeof(Node)); /* cria um novo no caso tenha sobrado memoria livre no no atual */
		newNode->tipo = 'L';
		newNode->prox = aux->prox;
		newNode->inicio = (aux->inicio + tamanho);
		newNode->tamanho = (aux->tamanho - tamanho);
		newNode->quickprox = lista[newNode->tamanho-1];
		lista[newNode->tamanho-1] = newNode;

		aux->prox = newNode;
		aux->tamanho = tamanho;
		aux->tipo = 'P';
		aux->quickprox = NULL;
	}
	else {
		aux->tipo = 'P';
		aux->quickprox = NULL;
	}
	
	escreveBin(pid, arquivo, aux->inicio, tamanho);

	return aux->inicio;
}