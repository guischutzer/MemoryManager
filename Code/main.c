/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils.h"
#include "io.h"


int main() {
    char*  input, shell_prompt[MAXCHAR];
    char** argv;
    int pag = 0, fit = 0, nproc = 0;
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

	        nproc = carrega(argv[1], &total, &virtual, lista_proc);
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
    				printf("Comando desconhecido.\n");
    				return 1;
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
    				printf("Comando desconhecido.\n");
    				return 1;
    				break;
    		}
    	}
    	else if (strcmp(argv[0], "executa") == 0) {
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
    			

    		}
    	}
    	else if (strcmp(argv[0], "sai") == 0) {
    		printf("Adeus.\n");
    		break;
    	}

    if(lista_proc != NULL)
        liberaListaProcessos(lista_proc, nproc);

    if (argv != NULL)
    	free(argv);

    if (ftotal != NULL)
    	free(ftotal);

    if (fvirtual != NULL)
    	free(fvirtual);

    }
    return 0;
}
