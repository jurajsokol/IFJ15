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

	//tokeny
	S_POINT,	// 01 .
	S_COLON,	// 02 :
	S_SCOL,		// 03 ;
	S_MUL,		// 04 *
	S_DIV,		// 05 /
	S_ADD,		// 06 +
	S_SUB,		// 07 -
	S_LOW,		// 08 <
	S_GRE,		// 09 >
	S_LOWEQ,	// 10 <=
	S_GREEQ,	// 11 >=
	S_EQ,		// 12 =
	S_EQ2,		// 13 ==
	S_NEQ,		// 14 !=
	S_EXCL,		// 15 !
	S_LRB,		// 16 (
	S_RRB,		// 17 )
	S_LSB,		// 18 [
	S_RSB,		// 19 ]
	S_LCB,		// 20 {
	S_RCB,		// 21 }
	S_QUOT,		// 22 "
	S_EOF,		// 23 koniec suboru

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

	//pomocne stavy
	S_ID,		// identifikator - ak zacina pismenom alebo _
	S_NUM,		// cislo
	S_EXP,		//exponent - e, E
	S_ESC,		// escape sekvencia
	S_ZERO,		// prebytocne pociatocne 0
	S_RCOM,		// riadkovy komentar
	S_BCOM,		// blokovy komentar
	S_COMEND,	// mozny koniec blokoveho komentara

} tState;

char *Token(tState*, FILE*);
void TokAddChar(char *, int *, unsigned char);
void LexError();

#endif
