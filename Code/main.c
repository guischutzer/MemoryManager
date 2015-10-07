/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils.h"
#include "io.h"

void firstFit(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){
	Node *headtot, *headvirt, *aux;
	struct timeval tv, inicio, fim;
	double totime, ultime = -1, espera, tf;

	headtot = NULL;
	headvirt = NULL;
	aux = NULL;
	
	headtot = malloc(sizeof(Node));
	headtot->tipo = 'L';
	headtot->inicio = 0;
	headtot->tamanho = total;
	headtot->prox = NULL;

	headvirt = malloc(sizeof(Node));
	headvirt->tipo = 'L';
	headvirt->inicio = 0;
	headvirt->tamanho = virtual;
	headvirt->prox = NULL;	

	gettimeofday(&tv, NULL);
	inicio = tv;

	while(1){
		gettimeofday(&tv, NULL);
		fim = tv;
		totime = (double) fim.tv_sec + fim.tv_usec/10e6 - (inicio.tv_sec + fim.tv_usec/10e6);
		if(totime != ultime){
			ultime = totime;
			printf("total = %f\n", totime);
		if(totime == 10)
			break;
		}
	}

}

void nextFit(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}

void quickFit(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}

void NRUP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}

void FIFO(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}

void SCP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}

void LRUP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc){

}


int main() {
    char*  input, shell_prompt[MAXCHAR];
    char** argv;
    int pag = 0, fit = 0, nproc = 0, intv = 0;
    int total = 0, virtual = 0;
    int i = 0;
    FILE *ftotal = NULL, *fvirtual = NULL;
    Processo *lista_proc = NULL;

    lista_proc = NULL;

    while(1) {

	    snprintf(shell_prompt, sizeof(shell_prompt), "[ep2] ");
	    input = readline(shell_prompt);
	    add_history(input);
    	argv = tokenize(input);

    	if (strcmp(argv[0], "carrega") == 0) {
    		printf("Modo carrega.\n");
      		if(lista_proc != NULL)
        		liberaListaProcessos(lista_proc, nproc);

	        lista_proc = carrega(argv[1], &total, &virtual, &nproc);
	        printf("total = %d, virtual = %d.\n", total, virtual);
	        printf("numero de processos = %d.\n", nproc);
	        if(lista_proc == NULL && nproc > 0){
	        	printf("ERRO: Nenhum dos processos foi armazenado corretamente.\n");
	        	return 1;
	        }

	        for (i = 0; i < nproc; i++)
	        	imprimeProc(lista_proc[i]);

    	}
    	else if (strcmp(argv[0], "espaco") == 0) {
    		pag = 0;
    		fit = atoi(argv[1]);
    		switch(atoi(argv[1])){
    			case 1 :
    				printf("Gerencia First Fit.\n");
    				break;
    			case 2 :
    				printf("Gerencia Next Fit.\n");
    				break;
    			case 3 :
    				printf("Gerencia Quick Fit.\n");
    				break;
    			default :
    				printf("Comando desconhecido. Por favor insira outro comando.\n");
    				fit = 0;
    				break;
    		}
    	}
    	else if (strcmp(argv[0], "substitui") == 0) {
    		fit = 0;
    		pag = atoi(argv[1]);
    		switch(atoi(argv[1])){
    			case 1 :
    				printf("Substituicao Not Recently Used Page.\n");
    				break;
    			case 2 :
    				printf("Substituicao First-In, First-Out.\n");
    				break;
    			case 3 :
    				printf("Substituicao Second-Chance Page.\n");
    				break;
    			case 4 :
    				printf("Substituicao Least Recently Used Page.\n");
    				break;
    			default :
    				printf("Comando desconhecido. Por favor insira outro comando.\n");
    				pag = 0;
    				break;
    		}
    	}

    	else if (strcmp(argv[0], "imprime") == 0) {
    		if (lista_proc != NULL){
    			for (i = 0; i < nproc; i++)
	        		imprimeProc(lista_proc[i]);
    		}
    		else printf("Carregue um arquivo para imprimir.\n");
    	}

    	else if (strcmp(argv[0], "executa") == 0) {
    		if (argv[1] != NULL){
    			intv = atoi(argv[1]);
    			printf ("Intervalo definido como %d.\n", intv);
    		}
    		else printf ("Nenhum intervalo definido.\n");


    		if(pag==0 && fit == 0){
    			printf("Escolha um algoritmo de gerenciamento antes de executar.\n");
    		}
    		
    		else if (total == 0 && virtual == 0) {
    			printf ("Carregue um arquivo antes de executar.\n");
    		}

    		else {
    			printf("Iniciando execucao do simulador...\n");
    			ftotal = fopen("/tmp/ep2.mem","wb");
    			if (ftotal != NULL)
    				printf ("ftotal aberto com sucesso!\n");
    			else {
    				printf ("ERRO: falha ao criar o arquivo ftotal.\n");
    				return 1;
    			}

    			criabin(total, ftotal);
    			
    			fvirtual = fopen("/tmp/ep2.vir","wb");
    			if (fvirtual != NULL)
    				printf ("fvirtual aberto com sucesso!\n");
    			else {
    				printf ("ERRO: falha ao criar o arquivo fvirtual.\n");
    				return 1;
    			}

    			criabin(virtual, fvirtual);
    			

    			if (fit != 0){
    				switch(fit){
    					case 1 :
    						printf("Gerencia First Fit.\n");
    						firstFit(nproc, total, virtual, intv, ftotal, fvirtual, lista_proc);
    						break;
    					case 2 :
    						printf("Gerencia Next Fit.\n");
    						nextFit(nproc, total, virtual, intv, ftotal, fvirtual, lista_proc);
    						break;
    					case 3 :
    						printf("Gerencia Quick Fit.\n");
    						quickFit(nproc, total, virtual, intv, ftotal, fvirtual, lista_proc);
    						break;
    					default :
    						break;
    				}
    			}
    			else {
    				switch(pag){
    					case 1 :
    						printf("Substituicao Not Recently Used Page.\n");
    						NRUP(nproc, total, virtual, intv, ftotal, fvirtual, lista_proc);
    						break;
    					case 2 :
    						printf("Substituicao First-In, First-Out.\n");
    						FIFO(nproc, total, virtual, intv, ftotal, fvirtual, lista_proc);
    						break;
    					case 3 :
		    				printf("Substituicao Second-Chance Page.\n");
		    				SCP(nproc, total, virtual, intv, ftotal, fvirtual, lista_proc);
		    				break;
		    			case 4 :
		    				printf("Substituicao Least Recently Used Page.\n");
		    				LRUP(nproc, total, virtual, intv, ftotal, fvirtual, lista_proc);
		    				break;
		    			default :
		    				break;
    				}
    			}	
    		}
    	}
    	else if (strcmp(argv[0], "sai") == 0) {
    		printf("Adeus.\n");
    		break;
    	}
    }

    if(lista_proc != NULL)
        liberaListaProcessos(lista_proc, nproc);

    if (argv != NULL)
    	free(argv);

    if (ftotal != NULL)
    	free(ftotal);

    if (fvirtual != NULL)
    	free(fvirtual);

    return 0;
}