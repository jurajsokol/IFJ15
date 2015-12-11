#include "sa.h"

int main(int argc, char *argv[]){
	if(argc == 1) // program je volaný bez argumentov, nemá čo psracovať
		return -1;

	FILE *fp;

	fp = fopen(argv[1],"r");
  	if (fp == NULL)
  	{
    	fprintf(stderr, "Open file error!\n");
    	return -1;
  	}

	printf("%d\n", syntakticka_analyza(fp));

	fclose(fp);

	return 0;
}
