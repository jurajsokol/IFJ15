/*
 * Projekt: Interpret jazyka IFJ15
 * Soubor: symbols.c
 * Popis: tabulka symbolů
 * Autor: Lukáš Matula (xmatul26)
 */


#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "variables.h"


/***
 * TSymbolType
 *   symbol je jedním z těchto typů
 */
typedef enum
        {
          stVariable,   // z počátku je každý identifikátor proměnná
          stLabel       // některé jsou labely
        } TSymbolType;



/***
 * TSymbols
 *   struktura symbolu
 */
typedef struct _TSymbol
        TSymbol, *PSymbol;



/***
 * TSymbols
 *  struktura zastřešující tabulku symbolů
 */ 
typedef struct _TSymbols
        TSymbols, *PSymbols;



/***
 * SymbolsCreate()
 *   Vytvoří prázdnou tabulku symbolů a vrátí na ukazatele na něj
 */ 
PSymbols SymbolsCreate();



/***
 * SymbolsInsert()
 *   funkce vloží symbol do tabulky, jestliže už existuje, vrátí
 *   ukazatel na nej, jinak provede vlozeni a take vrati ukazatel na nej.
 *   Parametrem je nazev symbolu
 */ 
PSymbol SymbolsInsert(PSymbols table, char *strName, PVariableTable vartable);



/***
 * SymbolsSetLabel()
 *   udela z identifikatoru label
 *   1. parametr je adresa symbolu , kterou vrací f-ce SymbolsInsert()
 *   2. parametr je index do pasky, kam label ukazuje
 *   jestliže se pokusí redefinovat, vrací nenulovou hodnotu, jinak vrací 0
 */
int SymbolsSetLabel(PSymbol symbol, unsigned index);



/***
 * SymbolsGetType()
 *   funkce pro semantic, ktera vrati typ symbolu
 *   parametr je adresa symbolu 
 */
TSymbolType SymbolsGetType(PSymbol symbol);



/***
 * SymbolsGetName()
 *   funkce pro semantic, ktera vrati jmeno symbolu (pro vypis chyb)
 *   parametr je adresa symbolu
 */
char *SymbolsGetName(PSymbol symbol);



/***
 * SymbolsGetLabelIndex()
 *   funkce pro semantic, ktera vrati index do pasky u labelu
 *   parametr e adresa symbolu  
 */
unsigned SymbolsGetLabelIndex(PSymbol symbol);



/***
 * SymbolsGetVariable()
 *   funkce pro semantic, ktera vrati odkaz na promenou 
 *   parametr je adresa symbolu 
 */
PVariable SymbolsGetVariable(PSymbol symbol);



/***
 * SymbolsDestroy()
 *   uvolni vsechny symboly + tabulku symbolu z pameti
 *   parametr je adresa tabulky symbolu  
 */ 
void SymbolsDestroy(PSymbols table);

#endif
