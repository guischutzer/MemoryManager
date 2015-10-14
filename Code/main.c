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
#include <readline/readline.h>
#include <readline/history.h>
#include "utils.h"
#include "fit.h"
#include "page.h"
#include "io.h"

void executa(Processo* lista_proc, FILE *ftotal, FILE *fvirtual, int total, int virtual, int nproc, int fit, int pag, int intv){
  Node *aux = NULL, *headtot, *headvirt, **headquick;
  Page *lista_pags = NULL;
  Frame *lista_frames = NULL;
  Acesso *a = NULL;
  Processo p;

  struct timeval tv, inicio, fim;
  double totime, ultime = -1;
  int proc_fim = 0, proc_ini = 0;
  int nquadros = 0;
  int i, j, map;

  if (fit == 0) fit = 3;
  if (pag == 0) pag = 1;

  nextNode = NULL;
  headquick = NULL;

  if(lista_proc == NULL) {
    printf("Carregue um arquivo para executar.\n");
    return;
  }
  if (!nproc){
    printf("Nenhum processo, carregue outro arquivo.\n");
    return;
  }

  if (fit == 0){
    printf("Nenhum algoritmo de Fit escolhido.\n");
    return;
  }
  else if (pag == 0){
    printf("Nenhum algoritmo de substituição de página escolhido.\n");
    return;
  }


	headvirt = malloc(sizeof(Node));
	headvirt->tipo = 'L';
	headvirt->inicio = 0;
	headvirt->tamanho = virtual;
	headvirt->prox = NULL;
	headvirt->quickprox = NULL;

	if (fit == 3) {
		headquick = malloc((virtual)*sizeof(Node*));
		for (i = 0; i < virtual-1; i++)
			headquick[i] = NULL;
		headquick[i] = headvirt;
	}

  lista_pags = malloc((virtual) * sizeof(Page));
  for(i = 0; i < virtual; i++){
    lista_pags[i].pid = -1;
    lista_pags[i].pos = -1;
    lista_pags[i].map = -1;
  }

  lista_frames = malloc((total) * sizeof(Frame));
  for(i = 0; i < total; i++){
    lista_frames[i].pid = -1;
    lista_frames[i].R = 0;
  }


  gettimeofday(&tv, NULL);
  inicio = tv;

  while(proc_fim < nproc){ /* enquanto o numero de processos terminados for menor do que o numero de processos */
    gettimeofday(&tv, NULL);
    fim = tv;

		totime = (double) fim.tv_sec + fim.tv_usec/10e6 - (inicio.tv_sec + fim.tv_usec/10e6);

    if(totime != ultime){
			ultime = totime;
      /* Checa quais processos ja terminaram */
      for(i = 0; i < proc_ini; i++){
        if(lista_proc[i].tf <= ultime && lista_proc[i].init >= 0){
          proc_fim++;
          escreveBin(-1, fvirtual, lista_proc[i].init, lista_proc[i].b);

          switch(fit){
            case 1: /* FirstFit */
              aux = headvirt;
              while(aux != NULL){
                if(aux->inicio == lista_proc[i].init){
                  aux->tipo = 'L';
                  break;
                }
                aux = aux->prox;
              }
              mergeNode(headvirt, headquick);
              break;
            case 2: /* NextFit */
              aux = headvirt;
              while(aux != NULL){
                if(aux->inicio == lista_proc[i].init){
                  aux->tipo = 'L';
                  break;
                }
                aux = aux->prox;
              }
              mergeNode(headvirt, headquick);
              break;
            case 3: /* QuickFit*/
              aux = headvirt;
              while(aux != NULL){
                if(aux->inicio == lista_proc[i].init){
                  aux->tipo = 'L';
                  aux->quickprox = headquick[aux->tamanho-1];
                  headquick[aux->tamanho-1] = aux;
                  break;
                }
                aux = aux->prox;
              }
              mergeNode(headvirt, headquick);
              break;
          }


          switch(pag){
            case 1: /* NRUP */
              break;
            case 2: /* FIFO */
              break;
            case 3: /* SCP */
              break;
            case 4: /* LRUP */
              break;
          }

          /* Tira as páginas e quadros dos processos que acabaram */
          for(j = 0; j < lista_proc[i].b; j++){
            p = lista_proc[i];
            lista_pags[p.init + j].pid = -1;
            lista_pags[p.init + j].pos = -1;
            if(lista_pags[p.init + j].map != -1){
              escreveBin(-1, ftotal, lista_pags[p.init + j].map, 1);
              lista_frames[lista_pags[p.init + j].map].pid = -1;
              lista_frames[lista_pags[p.init + j].map].R = 0;
              lista_pags[p.init + j].map = -1;
            }
          }
          lista_proc[i].init = -1;
        }
      }

      /* Percorre listas de acessos e checa quais devem ser feitos */
      for(i = 0; i < proc_ini; i++){
        for(a = lista_proc[i].head; a != NULL; a = a->prox){
          if(a->inst <= ultime){
            map = lista_pags[lista_proc[i].init + a->pos].map;
            if(map == -1) /* PageFault! Chamamos algum algoritmo de substituicao*/ {
              switch(pag){
                case 1: /* NRUP */
                  break;
                case 2: /* FIFO */
                  break;
                case 3: /* SCP */
                  break;
                case 4: /* LRUP */
                  break;
              }
            }
          }
        }
      }

      while(lista_proc[proc_ini].t0 == ultime){
        switch(fit){
        	case 1: /* FirstFit */
            lista_proc[proc_ini].init = firstFit(fvirtual, proc_ini, lista_proc[proc_ini].b, headvirt);
            break;
		      case 2: /* NextFit */
            lista_proc[proc_ini].init = nextFit(fvirtual, proc_ini, lista_proc[proc_ini].b, headvirt);
            break;
          case 3: /* QuickFit*/
            lista_proc[proc_ini].init = quickFit(fvirtual, proc_ini, lista_proc[proc_ini].b, headquick, virtual);
            break;
        }
        p = lista_proc[proc_ini];
        for(i = 0; i < p.b; i++){
          lista_pags[p.init + i].pid = proc_ini;
          lista_pags[p.init + i].pos = i;
          lista_pags[p.init + i].map = -1;
        }
        proc_ini++;
      }
      if ((int) ultime % intv == 0){

          printf("Instante atual: %d\n", (int) ultime);

          printf("Paginas (memoria virtual):\n");
          imprimePags(lista_pags, virtual);
          printf("Quadros (memoria fisica):\n");
          imprimeFrames(lista_frames, total);

          /*printf("Arquivo binario da memoria total: \n");
          imprimeBin(ftotal, total*16);
          printf("Arquivo binario da memoria virtual: \n");
          imprimeBin(fvirtual, virtual*16);
          printf ("\n");*/
      }

    }

  }
  printf ("Simulacao terminada no instante %d\n", (int) ultime);
  if(lista_pags != NULL) free(lista_pags);
  if(lista_frames != NULL) free(lista_frames);
  if(headquick != NULL) free(headquick);
}

int main(){
  char*  input, shell_prompt[MAXCHAR];
  char** argv = NULL;
  int pag = 0, fit = 0, nproc = 0, intv = 0;
  int total = 0, virtual = 0;
  int i = 0, procs = 0;
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
      procs = 1;
  	}
    else if (strcmp(argv[0], "imprime") == 0){
      if (lista_proc != NULL){
        for (i = 0; i < nproc; i++)
          imprimeProc(lista_proc[i]);
      }
      else
        printf("Não há processos.\n");
    }
  	else if (strcmp(argv[0], "espaco") == 0) {
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
  			printf("Intervalo definido como %d.\n", intv);
		  }
  		else intv = 1;

			printf("Iniciando execucao do simulador...\n");
			ftotal = fopen("/tmp/ep2.mem","wb+");
			if (ftotal != NULL)
				printf("ftotal aberto com sucesso!\n");
			else {
				printf("ERRO: falha ao criar o arquivo ftotal.\n");
				return 1;
  	  }

  		escreveBin(-1, ftotal, 0, total);

			fvirtual = fopen("/tmp/ep2.vir","wb+");
			if (fvirtual != NULL)
				printf ("fvirtual aberto com sucesso!\n");
			else {
				printf ("ERRO: falha ao criar o arquivo fvirtual.\n");
				return 1;
			}

			escreveBin(-1, fvirtual, 0, virtual);
      executa(lista_proc, ftotal, fvirtual, total, virtual, nproc, fit, pag, intv);
  	}

  	else if (strcmp(argv[0], "sai") == 0) {
  		printf("Adeus.\n");
  		break;
  	}

		else {
			printf("Lista de comandos:\n");
			printf("carrega <nome>    -- carrega um arquivo de entrada\n");
			printf("espaco <1-3>      -- escolhe entre os métodos FirstFit, NextFit e QuickFit\n");
			printf("substitui <1-4>   -- escolhe entre os métodos com substiuição de página: FIFO, NRUP, SCUP, LRUP\n");
			printf("imprime           -- imprime a lista de processos\n");
			printf("executa <inteiro> -- executa o método selecionado com a entrada carregada; opcional: número de segundos para imprimir o estado dos arquivos (default = 1)\n");
			printf("sai               -- encerra o programa\n");
		}
  }

  if(procs == 1){
      liberaListaProcessos(lista_proc, nproc);
  }

  if (argv != NULL)
  	free(argv);

  if (ftotal != NULL)
  	free(ftotal);

  if (fvirtual != NULL)
  	free(fvirtual);

  return 0;
}
