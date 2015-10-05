/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#define TRUE	1
#define FALSE	0
#define MAXCHAR 100

char** tokenize(char* str);

typedef struct{
    char   nome[MAXCHAR];
    int    inicio;
    int    duracao;
    int    fim;
	int    prioridade;
	int    core;
} Thread;
