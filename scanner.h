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
	S_HASH,		// 23 #
	S_COMA,		// 24 ,
	S_EOF,		// 25 koniec suboru

	// klucove slova
	S_AUTO,		// 26 auto
	S_CIN,		// 27 cin
	S_COUT,		// 28 cout
	S_DOUB,		// 29 double
	S_ELSE,		// 30 else
	S_FOR,		// 31 for
	S_IF,		// 32 if
	S_INT,		// 33 int
	S_RET,		// 34 return
	S_STR,		// 35 string

	//pomocne stavy
	S_ID,		// 36 identifikator - ak zacina pismenom alebo _
	S_NUM,		// 37 cislo
	S_EXP,		// 38 exponent - e, E
	S_ESC,		// 39 escape sekvencia
	S_ZERO,		// 40 prebytocne pociatocne 0
	S_FLOAT,	// 41 desatinne cislo
	S_RETAZ,	// 42 retazec
	S_RCOM,		// 43 riadkovy komentar
	S_BCOM,		// 44 blokovy komentar
	S_COMEND,	// 45 mozny koniec blokoveho komentara
	S_LOAD,		// 46 nacitanie hodnoty zo vstupu >>
	S_WRITE,	// 47 vypis hodnot <<
	S_SCOPE,	// 48 ::
	S_PLUS,		// 49 rozsirenie - unarny +
	S_MINUS,	// 50 rozsirenie - unarny -
	S_REAL_PART, //51 realna cast
	S_FLOATEXP,	// 52 desatinny exponent
	S_EXP_ZERO,	// 53 nula v exponente
	S_INCL,		// 54 include
	S_DEF,		// 55 define 

} tState;

char *Token(tState*, FILE*);
void TokAddChar(char *, int *, unsigned char);
void LexError();

#endif
