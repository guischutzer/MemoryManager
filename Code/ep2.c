
/*

MAC0422 - Sistemas Operacionais
    EP2 - 05/10/2015

Guilherme Souto Schützer     - 8658544
Tomás Marcondes Bezerra Paim - 7157602

*/

#include <stdio.h>
#include "utils.h"

int main(int argc, char const *argv[]) {

  FILE            *entrada;
  char            linha[MAXCHAR];
  int i,j;

  entrada = fopen(argv[1], "r");

  for(i = 0; fgets(linha, MAXCHAR, entrada); i++){
    tokens = tokenize(linha);
    for(j = 4; tokens[i - 1] != NULL; j++)
      printf("%d: tokens[%d] = %s\n", i, j, tokens[j]);
  }

  return 0;
}
