/*
* Projekt: Interpret jazyka IFJ15
* Subor: scanner.c
* Popis: Lexikalny analyzator
* Autor: Alexandra Uhrinova (xuhrin01)
*/

#include "scanner.h"
#include "libraries.h"

void LexError()
{
	fprintf(stderr, "LEX ERROR\n");
	exit(1);
}