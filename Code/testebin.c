#include <stdio.h>

	void criabin(int t, FILE *arquivo)
	{
		int i;
		char c = -1;
		for (i = 0; i < t; i++){
			printf("t = %d\n", t);
			fwrite(&c, sizeof(char), 1, arquivo);
		}
	}

	int main()
	{
		FILE *ptr_myfile;

		ptr_myfile=fopen("test.bin","wb");
		if (!ptr_myfile)
		{
			printf("Unable to open file!");
			return 1;
		}
		criabin(30, ptr_myfile);
		fclose(ptr_myfile);
		return 0;
	}
