#include <stdio.h>



	void imprimeBin(FILE* arquivo, int arqsize){
	int i;
	char c[1];

	c[0] = 5;

	for (i = 0; i < arqsize; i++)
		{
			fseek(arquivo, sizeof(char)*i-1, SEEK_SET);
			fread(c, 1, sizeof(c), arquivo);
			printf("%4d ", c[0]);
		}
		printf ("\n");
}

void escreveBin(char pid, FILE* arquivo, int origem, int pags){
	int i;

	printf("pid = %d\n", pid);
	printf("origem = %d, pags = %d\n", origem, pags);

	fseek(arquivo, sizeof(char)*origem*16, SEEK_SET);

	for(i = 0; i < pags*16; i++){
		fwrite(&pid, sizeof(pid), 1, arquivo);
	}
	printf("i = %d\n", i);
}

	void criabin(int t, FILE *arquivo)
	{
		int i;
		char c = 1;
		for (i = 0; i < t; i++){
			if (i%2 != 0){
				c = 0;
			}
			else {c = 1;}
			fwrite(&c, sizeof(c), 1, arquivo);
		}
	}

	int main()
	{
		FILE *ptr_myfile;

		ptr_myfile=fopen("test.bin","wb+");
		if (!ptr_myfile)
		{
			printf("Unable to open file!");
			return 1;
		}

		criabin(30, ptr_myfile);

		imprimeBin(ptr_myfile, 30);

		fclose(ptr_myfile);
		return 0;
	}
