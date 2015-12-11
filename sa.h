/*
* Projekt: Interpret jazyka IFJ15
* Subor: sa.h
* Popis: Syntaktický analyzátor
* Autor: Juraj Sokol (xsokol08)
*/

#include "libraries.h"

#ifndef SA_H
#define SA_H

#define FUNC 65
#define TYP 66
#define ARG 67
#define STAT 68
#define ID 69
#define DEC 70
#define EXP 71
#define ELSE 72
#define CIN 73
#define COUT 74
#define ARGSF 75
#define ARGS 76
#define BODY 77
#define INCL 78
#define EPS 80
#define VYRAZ 81

int syntakticka_analyza(FILE *fp);

#endif
