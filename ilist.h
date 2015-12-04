#ifndef ILIST_H_INCLUDED
#define ILIST_H_INCLUDED

#include stdio.h
#include stdlib.h
#include stdarg.h
#include malloc.h

#define I_STOP 0  /* Konec vykonavani */
#define I_BEGIN 1 /* Zacatek vykonavani*/
#define I_READ 2
#define I_WRITE 3
#define I_MULTIPLY 4 /*Nasobeni */
#define I_DIVIDE 5 /* Deleni */
#define I_ADD 6  /* Scitani */
#define I_SUB 7  /* Odcitani */
#define I_IF 8
#define I_ELSE 9
#define I_END_IF 10
#define I_INT_LENGTH 11
#define I_STRING_SUBSTR 12
#define I_STRING_CONCAT 13
#define I_INT_FIND 14
#define I_STRING_SORT 15
#define I_FOR 16
#define I_END_FOR 17



typedef struct
{
  int acitce;  // typ instrukce
  void *addr1; // adresa 1
  void *addr2; // adresa 2
  void *addr3; // adresa 3
} tInstr;

typedef struct listItem
{
  tInstr Instruction;
  struct listItem *nextItem;
} tListItem;

typedef struct
{
  struct listItem *first;  // ukazatel na prvni prvek
  struct listItem *last;   // ukazatel na posledni prvek
  struct listItem *active; // ukazatel na aktivni prvek
} tListOfInstr;

void listInit(tListOfInstr *L); /* inicializuje seznam */
void listFree(tListOfInstr *L); /* dealokace seznamu */
void listInsertLast(tListOfInstr *L, tInstr I); /* vlozi hodnotu na konec seznamu */
void listInsertFirst(tListOfInstr *L, tInstr I); /* vlozi hodnotu na zacatek seznamu */
void listFirst(tListOfInstr *L); /* nastavi prni prvek jako aktivni  */
void listNext(tListOfInstr *L); /* aktivni bude nasledujici prvek */
void DeleteFirst (tListOfInstr *L); /* odstrani prvni prvek */
void listGoto(tListOfInstr *L, void *gotoInstr); /* nastavime aktivni instrukci podle zadaneho ukazatele */
void *listGetPointerLast(tListOfInstr *L); /* vrati ukazatel na posledni instrukci */
tInstr *listGetData(tListOfInstr *L); /* vrati aktivni instrukci */


#endif // ILIST_H_INCLUDED
