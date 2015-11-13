/*
* Projekt: Interpret jazyka IFJ15
* Subor: scanner.c
* Popis: Lexikalny analyzator
* Autor: Alexandra Uhrinova (xuhrin01)
*/

#include "scanner.h"
#include "libraries.h"

void TokAddChar(char *tok, int *tokLen, unsigned char c)
{
	(*tokLen)++;
	tok = (char*) realloc(tok, sizeof(char) * (*tokLen));	//realokacia pamate pre dalsi znak
	if(tok == NULL)
	{
		fprintf(stderr, "Memory allocation error!!!\n");
		exit(99);
	}
	tok[(*tokLen - 2)] = c;	//novy znak sa prida na koniec tokenu
	tok[(*tokLen - 1)] = '\0';	//retazec musi obsahovat prazdny znak na konci
}

char *Token(tState *retState, FILE *fp)
{
	int tokLen = 1;	//pociatocna dlzka tokenu
	char *tok = (char*) malloc(sizeof(char));	//alokacia miesta pre prazdny znak
	char znak; 
	tState state = S_START;

	while((znak = getc(fp)) != EOF)
	{		
		TokAddChar(tok, &tokLen, znak);
	}

	*retState = state;	//vraciam ID tokenu
	return tok;
}

void LexError()
{
	fprintf(stderr, "LEX ERROR\n");
	exit(1);
}
