/*
* Projekt: Interpret jazyka IFJ15
* Subor: sa_výrazov.h
* Popis: Hlavicka pre syntaktický analyzátor výrazov
* Autor: Juraj Sokokol (xsokol08)
*/

#define E 60 // neterminál
#define DOLAR 61

int analyza();
char precedencna_tabulka(int t_x,int t_y);
