#include <stdio.h>

	

	void imprimeBin(FILE* arquivo, int arqsize){
	int i;
	char c[1];

	c[0] = 5;
	
	for (i = 0; i < arqsize; i++)
		{
			fseek(arquivo, sizeof(char)*i, SEEK_SET);
			fread(c, 1, sizeof(c), arquivo);
			printf("%d ", c[0]);
		}
		printf ("\n");
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
		FILE *ptr_myfile, *ptr_read;
		int counter;
		char c[1];

		c[0] = 7;

		ptr_myfile=fopen("test.bin","wb+");
		if (!ptr_myfile)
		{
			printf("Unable to open file!");
			return 1;
		}
		
		criabin(30, ptr_myfile);

		
		imprimeBin(ptr_myfile, 30);

		/* fseek(ptr_read, sizeof(char), SEEK_SET); */
		fread(c, 1, sizeof(c), ptr_myfile);
		printf("%d ", c[0]);
		/* fseek(ptr_read, sizeof(char)*2, SEEK_SET);*/
		fread(c, 1, sizeof(c), ptr_myfile);
		printf("%d ", c[0]);
		printf("\n");

		for ( counter=1; counter <= 30; counter++)
		{
			fread(c, sizeof(c), 1, ptr_myfile);
			printf("%d ", c[0]);
		}
		printf("\n");

		fclose(ptr_myfile);
		return 0;
	}
