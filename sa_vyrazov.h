/*
* Projekt: Interpret jazyka IFJ15
* Subor: sa_výrazov.h
* Popis: Hlavicka pre syntaktický analyzátor výrazov
* Autor: Juraj Sokokol (xsokol08)
*/

#ifndef SA_VYRAZOV_H
#define SA_VYRAZOV_H

#define E 60 // neterminál používaný v s.a. výrazov
#define DOLAR 61

int analyza();
void FreeToken(char *vstup);
void SAError();

#endif
