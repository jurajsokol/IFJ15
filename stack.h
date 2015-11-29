/*
** Implementácia zásobníku - hlavičkový súbor
*/

#include "libraries.h"

typedef struct{
  int *data;
  int vrchol;
}STACK;

void Init(STACK *S);
void Push(STACK *S, char z);
int TopPop(STACK *S);
int Top(STACK *S);
int TopSec(STACK *S);
void Pop(STACK *S);
int Size(STACK *S);
int Empty(STACK *S);
void PrintS(STACK *S);
void FreeS(STACK *S);
