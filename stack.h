/*
* Projekt: Interpret jazyka IFJ15
* Subor: stack.h
* Popis: Implementácia dátovej štruktúry zásobník
* Autor: Juraj Sokol (xsokol08)
*/

#include "libraries.h"

typedef struct{
  int *data;
  int vrchol;
}STACK;

void InitS(STACK *S);
void PushS(STACK *S, char z);
int TopPopS(STACK *S);
int TopS(STACK *S);
int TopSecS(STACK *S);
void PopS(STACK *S);
int SizeS(STACK *S);
int EmptyS(STACK *S);
void PrintS(STACK *S);
void FreeS(STACK *S);
