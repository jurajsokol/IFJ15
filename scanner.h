/*
* Projekt: Interpret jazyka IFJ15
* Subor: scanner.h
* Popis: Hlavicka pre lexikalny analyzator
* Autor: Alexandra Uhrinova (xuhrin01)
*/

#include "libraries.h"

#ifndef SCANNER_H
#define SCANNER_H

typedef enum 
{
	S_START,	// 00 pociatocny stav
	S_POINT,	// .
	S_MUL,		// *
	S_DIV,		// /
	S_ADD,		// +
	S_SUB,		// -
	S_LOW,		// <
	S_GRE,		// >
	S_LOWEQ,	// <=
	S_GREEQ,	// >=
	S_EQ,		// ==
	S_NEQ,		// !=

	// klucove slova
	S_AUTO,		// auto
	S_CIN,		// cin
	S_COUNT,	// count
	S_DOUB,		// double
	S_ELSE,		// else
	S_FOR,		// for
	S_IF,		// if
	S_INT,		// int
	S_RET,		// return
	S_STR,		// string

} tState;

char *Token(tState*, FILE*);
void TokAddChar(char *, int *, unsigned char);
void LexError();

#endif
