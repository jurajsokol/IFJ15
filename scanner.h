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
	S_AUTO,		// 24 auto
	S_CIN,		// 25 cin
	S_COUNT,	// 26 count
	S_DOUB,		// 27 double
	S_ELSE,		// 28 else
	S_FOR,		// 29 for
	S_IF,		// 30 if
	S_INT,		// 31 int
	S_RET,		// 32 return
	S_STR,		// 33 string

	//pomocne stavy
	S_ID,		// 34 identifikator - ak zacina pismenom alebo _
	S_NUM,		// 35 cislo
	S_EXP,		// 36 exponent - e, E
	S_ESC,		// 37 escape sekvencia
	S_ZERO,		// 38 prebytocne pociatocne 0
	S_FLOAT,	// 39 desatinne cislo
	S_RETAZ,	// 40 retazec
	S_RCOM,		// 41 riadkovy komentar
	S_BCOM,		// 42 blokovy komentar
	S_COMEND,	// 43 mozny koniec blokoveho komentara
	S_LOAD,		// 44 nacitanie hodnoty zo vstupu >>
	S_WRITE,	// 45 vypis hodnot <<
	S_SCOPE,	// 46 ::
	S_PLUS,		// 47 unarny +
	S_MINUS,	// 48 unarny -

} tState;

char *Token(tState*, FILE*);
void TokAddChar(char *, int *, unsigned char);
void LexError();

#endif
