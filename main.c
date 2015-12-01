#include "scanner.h"
#include "libraries.h"
#include "sa_vyrazov.h"


int main(int argc, char *argv[]){
	if(argc == 1)
		return 1;
	FILE *fp;
	tState tokenType;
	char *vstup = NULL;
	fp = fopen(argv[1],"r");
  	if (fp == NULL)
  	{
    	fprintf(stderr, "Open file error!\n");
    	return 1;
  	}

	printf("SA výraz: %d\n", analyza(fp, vstup));
	free(vstup);
	while(1)
	{
		char *token = Token(&tokenType, fp);
		if(tokenType == S_EOF)
			break;
	    printf("%s - %d\n", token, tokenType);
			free(token);
	}

	fclose(fp);

	return 0;
}
