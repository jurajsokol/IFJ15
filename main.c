#include "scanner.h"
#include "libraries.h"


int main(int argc, char *argv[]){
	if(argc == 1)
		return 1;
	FILE *fp;
	tState tokenType;
	fp = fopen(argv[1],"r");
  	if (fp == NULL)
  	{
    	fprintf(stderr, "Open file error!\n");
    	return 1;
  	}

	printf("%s - %d\n", Token(&tokenType, fp), tokenType);
	fclose(fp);


	return 0;
}
