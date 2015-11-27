/*
** Implementácia zásobníku - hlavičkový súbor
*/

#include "libraries.h"

typedef struct{
  int data[100];
  int vrchol;
}STACK;

void Init(STACK *S);
void Push(STACK *S, char z);
char TopPop(STACK *S);
char Top(STACK *S);
void Pop(STACK *S);
int Size(STACK *S);
int Empty(STACK *S);
void PrintS(STACK *S);
