/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#define LIVRE NULL

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
		while ((aux->tipo == LIVRE) && (aux->prox != NULL) && (aux->prox->tipo == LIVRE)){
			aux->tamanho = (aux->tamanho + aux->prox->tamanho);
			morta = aux->prox;
			aux->prox = aux->prox->prox;
			free(morta);
		}
		aux = aux->prox;
	}
}


void firstFit(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){
	Node *headtot, *headvirt, *aux, *newNode;
	struct timeval tv, inicio, fim;
	double totime, ultime = -1;
	int i = 0, procfim = 0, encontrou = 0, pos = 0;
	char escreve;

	headtot = NULL;
	headvirt = NULL;
	aux = NULL;
	newNode = NULL;

	headtot = malloc(sizeof(Node));
	headtot->tipo = LIVRE;
	headtot->inicio = 0;
	headtot->tamanho = total;
	headtot->prox = NULL;

	headvirt = malloc(sizeof(Node));
	headvirt->tipo = LIVRE;
	headvirt->inicio = 0;
	headvirt->tamanho = virtual;
	headvirt->prox = NULL;

	gettimeofday(&tv, NULL);
	inicio = tv;

	while(procfim < nproc){ 	/* enquanto o numero de processos terminados for menor do que o numero de processos */
		gettimeofday(&tv, NULL);
		fim = tv;
		totime = (double) fim.tv_sec + fim.tv_usec/10e6 - (inicio.tv_sec + fim.tv_usec/10e6);

		if(totime != ultime){
			ultime = totime;

			/* checa se algum processo da memoria fisica terminou para tira-lo da memoria */
			aux = headtot;
			while(aux != NULL){
				if ((aux->tipo != LIVRE) && (aux->tipo->tf <= ultime)){
					aux->tipo = LIVRE; 	/* simplesmente dizemos que a memoria agora esta livre */
					procfim++;			/* incrementamos o contador de processos terminados */
					/* codigo que volta o arquivo binario correspondente para -1 */
					fseek(ftotal, aux->inicio, SEEK_SET);
					escreve = -1;
					for (pos = 0; pos < aux->tamanho; pos++)
						fwrite(&escreve, sizeof(char), 1, ftotal);

				}
				aux = aux->prox;
			}

			/* checa se algum processo da memoria virtual terminou para tira-lo da memoria */
			aux = headvirt;
			while(aux != NULL){
				if ((aux->tipo != LIVRE) && (aux->tipo->tf <= ultime)){
					aux->tipo = LIVRE; 	/* simplesmente dizemos que a memoria agora esta livre */
					procfim++;			/* incrementamos o contador de processos terminados */
					/* codigo que volta o arquivo binario correspondente para -1 */
					fseek(fvirtual, aux->inicio, SEEK_SET);
					escreve = -1;
					for (pos = 0; pos < aux->tamanho; pos++)
						fwrite(&escreve, sizeof(char), 1, fvirtual);
				}
				aux = aux->prox;
			}
			/* agora devemos checar se algum processo esta previsto para comecar no instante atual */

			mergeNode(headtot);

			mergeNode(headvirt);


			/* checar os vetores para ver se algum processo precisa de memoria */
			if (lista_proc[i].t0 == ultime){ /* assume que no maximo um processo vai entrar a cada instante */
				aux = headtot;
				encontrou = 0;
				while (aux != NULL){
					if ((aux->tipo == LIVRE) && (aux->tamanho >= lista_proc[i].b)){
						encontrou = 1;
						newNode = NULL;
						if (aux->tamanho > lista_proc[i].b){
							newNode = malloc(sizeof(Node)); /* cria um novo no caso tenha sobrado memoria livre no no atual */
							newNode->tipo = LIVRE;
							newNode->prox = aux->prox;
							newNode->inicio = (aux->inicio + lista_proc[i].b);
							newNode->tamanho = (aux->tamanho - lista_proc[i].b);

							aux->prox = newNode;
							aux->tamanho = lista_proc[i].b;
							aux->tipo = &(lista_proc[i]);

						}
						else {
							aux->tipo = &(lista_proc[i]);
						}
						fseek(ftotal, aux->inicio, SEEK_SET);
						escreve = i;
						for (pos = 0; pos < aux->tamanho; pos++)
							fwrite(&escreve, sizeof(char), 1, ftotal);
					}
					if (encontrou == 1)
						break;
					else
						aux = aux->prox;
				}
				if (encontrou == 0){

					aux = headvirt;
					while (aux != NULL){
						if ((aux->tipo == LIVRE) && (aux->tamanho >= lista_proc[i].b)){
							encontrou = 1;
							newNode = NULL;
							if (aux->tamanho > lista_proc[i].b){
								newNode = malloc(sizeof(Node)); /* cria um novo no caso tenha sobrado memoria livre no no atual */
								newNode->tipo = LIVRE;
								newNode->prox = aux->prox;
								newNode->inicio = (aux->inicio + lista_proc[i].b);
								newNode->tamanho = (aux->tamanho - lista_proc[i].b);

								aux->prox = newNode;
								aux->tamanho = lista_proc[i].b;
								aux->tipo = &(lista_proc[i]);

							}
							else {
								aux->tipo = &(lista_proc[i]);
							}
							/* escreve os bits no arquivo de memoria */
							fseek(fvirtual, aux->inicio, SEEK_SET);
							escreve = i;
							for (pos = 0; pos < aux->tamanho; pos++)
								fwrite(&escreve, sizeof(char), 1, fvirtual);
						}
						if (encontrou == 1)
							break;
						else
							aux = aux->prox;
					}
				}
				if (encontrou == 0)
					printf("ERRO: Memoria insuficiente.\n");
				i++;

			}


			if ((int) ultime % intv == 0){
					/* imprimeNode(headtot);
					imprimeNode(headvirt); */
					printf("Instante atual: %d\n", (int) ultime);
					printf("Arquivo binario da memoria total: \n");
					imprimeBin(ftotal, total);
					printf("Arquivo binario da memoria virtual: \n");
					imprimeBin(fvirtual, virtual);
					printf ("\n");
				}

		}

	}
	printf ("Simulacao terminada no instante %d\n", tatual);

}

void nextFit(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){
	return;
}

void quickFit(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}
