
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
    int pag = 0, fit = 0;
    int nproc, total, virtual;
    Processo lista_proc[MAXPROCESSOS];

    while(1) {

	    snprintf(shell_prompt, sizeof(shell_prompt), "[ep2] ");

	    input = readline(shell_prompt);

	    add_history(input);

    	argv = tokenize(input);

    	if (strcmp(argv[0], "carrega") == 0) {
    		printf("Modo carrega.\n");
        nproc = carrega(argv[1], &total, &virtual, lista_proc);
    	}
    	else if (strcmp(argv[0], "espaco") == 0) {
    		printf("Modo espaco %d.\n", atoi(argv[1]));
    		pag = 0;
    		fit = atoi(argv[1]);
    	}
    	else if (strcmp(argv[0], "substitui") == 0) {
    		printf("Modo substitui %d.\n", atoi(argv[1]));
    		fit = 0;
    		pag = atoi(argv[1]);
    	}
    	else if (strcmp(argv[0], "executa") == 0) {
    		printf("Modo executa.\n");
    	}
    	else if (strcmp(argv[0], "sai") == 0) {
    		printf("Modo sai.\n");
    		break;
    	}

    	free(argv);

    }
    return 0;
}
