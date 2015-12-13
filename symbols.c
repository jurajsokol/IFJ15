/*
 * Projekt: Interpret jazyka IFJ15
 * Soubor: symbols.c
 * Popis: tabulka symbolů
 * Autor: Lukáš Matula (xmatul26)
 */

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "symbols.h"
#include "variables.h"



/***
 * TSymbolAddr
 *   každému symbolu přidělena hodnota, u labelu je to index do pásky,
 *   u promenych adresa bunky v tabulce promennych (semantic)
 */
typedef union
        {
          unsigned LabelIndex;    // tohle je platny pro typ stLabel
          PVariable VariablePtr;  // a tohle pro stVariable
        } TSymbolAddr;

struct _TSymbol
       {
         char *name;         // jmeno symbolu, zároveň klíč
         TSymbolType type;   // typ symbolu (label/variable)
         TSymbolAddr addr;   // obsah (index labelu/adresa bunky promene)
         PSymbol LPtr, RPtr; // binarni strom
       };

/***
 * struct _TSymbols
 *   tabulka symbolů
 *   obsahem je pouze ukazatel na první prvek bin. stromu
 */
struct _TSymbols
       {
         PSymbol root;
       };

/***
 * SymError()
 * vypis chyby
 */
void SymError()
{
  printf("Chyba v práci se symboly, nebo s tabulkou symbolů\n");
  exit(10);
}


PSymbols SymbolsCreate()
{
  PSymbols table = (PSymbols)malloc(sizeof(TSymbols));
  if(table == NULL)
    SymError();
  table->root = NULL;
  return(table);
}


PSymbol SymbolInsert(PSymbol *parent, char *name, PVariableTable vartable)
{
#ifndef NDEBUG
  if(parent == NULL)
    SymError();
  if(name == NULL)
    SymError();
#endif
  if(*parent == NULL) //existuje prvek?
  {
    PSymbol symbol = (PSymbol)malloc(sizeof(TSymbol)); //nalezli jsme, zde vkládáme
    if(symbol == NULL)
      SymError();
    symbol->name = name;
    symbol->type = stVariable; //kazdy identifikator je zpocatku promenna
    symbol->addr.VariablePtr = VariablesInsert(vartable); //vytvorime zaznam v tabulce promennych
    symbol->LPtr = symbol->RPtr = NULL;
    *parent = symbol;
    return(symbol);
  }
  else
  {
    if(0 == strcmp((*parent)->name,name)) //zjistime, zda-li uz tam neni
    {
      free(name);
      return(*parent);
    }
    }
      if(0 < strcmp((*parent)->name,name)) //jeslti je vlevo, nebo vpravo
        return( SymbolInsert( &((*parent)->RPtr), name, vartable) );
      else
        return( SymbolInsert( &((*parent)->LPtr), name, vartable) );
}


PSymbol SymbolsInsert(PSymbols table, char *strName, PVariableTable vartable)
{
#ifndef NDEBUG
  if(strName == NULL)
    SymError();
  if(table == NULL)
    SymError();
#endif
  return(SymbolInsert(&(table->root),strName,vartable));
}


int SymbolsSetLabel(PSymbol symbol, unsigned index)
{
#ifndef NDEBUG
  if(symbol == NULL)
    SymError();
#endif
  if(symbol->type == stLabel)
    return(1);
  symbol->type = stLabel;
  symbol->addr.LabelIndex = index;
  return(0);
}


void SymbolDestroy(PSymbol root)
{
  if(root == NULL) //symbol = navrat z rekurze
    return;
  SymbolDestroy(root->LPtr);
  SymbolDestroy(root->RPtr);
  free(root->name);
  free(root);
}


void SymbolsDestroy(PSymbols table)
{
#ifndef NDEBUG
  if(table == NULL)
    SymError();
#endif
  SymbolDestroy(table->root);
  free(table);
}


TSymbolType SymbolsGetType(PSymbol symbol)
{
#ifndef NDEBUG
  if(symbol == NULL)
    SymError();
#endif
  return(symbol->type);
}


char *SymbolsGetName(PSymbol symbol)
{
#ifndef NDEBUG
  if(symbol == NULL)
    SymError();
#endif
  return(symbol->name);
}


unsigned SymbolsGetLabelIndex(PSymbol symbol)
{
#ifndef NDEBUG
  if(symbol == NULL)
    SymError();
  if(symbol->type != stLabel)
    SymError();
#endif
  return(symbol->addr.LabelIndex);
}


PVariable SymbolsGetVariable(PSymbol symbol)
{
#ifndef NDEBUG
  if(symbol == NULL)
    SymError();
  if(symbol->type != stVariable)
    SymError();
#endif
  return(symbol->addr.VariablePtr);
}
