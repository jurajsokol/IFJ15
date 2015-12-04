/*
* Projekt: Interpret jazyka IFJ15
* Soubor: ilist.c
* Popis: instrukcni list
* Autor: Stepan Smolka (xsmolk02)
*/


#include <stdio.h>
#include <malloc.h>
#include "ilist.h"

void listInit(tListOfInstr *L)
{
  L->first  = NULL;
  L->last   = NULL;
  L->active = NULL;
}

void listFree(tListOfInstr *L)
{
  tListItem *ptr;
  while (L->first != NULL)
  {
    ptr = L->first;
    L->first = L->first->nextItem;
    free(ptr);
  }
}

void listInsertLast(tListOfInstr *L, tInstr I)
// vlozi novou instruci na konec seznamu
{
   tListItem *newItem;
  newItem = malloc(sizeof (tListItem));
  if(newItem == NULL)
      listFree(L);

  newItem->Instruction = I;
  newItem->nextItem = NULL;

  if (L->first == NULL)
     L->first = newItem;
  else
     L->last->nextItem=newItem;

  L->last=newItem;

  return;
}

void listInsertFirst(tListOfInstr *L, tInstr I)
{
  tListItem *newItem;
  newItem = malloc(sizeof (tListItem));
  if(newItem == NULL)
      listFree(L);

  newItem->Instruction = I;
  newItem->nextItem = L->first;

  if((L->last == NULL) || (L->first == NULL)) L->last=newItem;

  L->first=newItem;
  return;
}

void listFirst(tListOfInstr *L)
{
  L->active = L->first;
}

void listNext(tListOfInstr *L)
{
  if (L->active != NULL)
    L->active = L->active->nextItem;

  else
    L->active = NULL;
}

void DeleteFirst (tInstList *L)
{
 if(L->first != NULL)
   {
   tListItem *newItem;

   if(L->active == L->first) L->active = NULL;
   newItem = L->first;
   L->first = L->First->nextItem;
   free(newItem);
   }

 return;
  }

void listGoto(tListOfInstr *L, void *gotoInstr)
{
  L->active = (tListItem*) gotoInstr;
}

void *listGetPointerLast(tListOfInstr *L)

{
  return (void*) L->last;
}

tInstr *listGetData(tListOfInstr *L)
{
  if (L->active == NULL)
  {
    printf("Chyba, zadna instrukce neni aktivni");
    return NULL;
  }
  else return &(L->active->Instruction);
}
