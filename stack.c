/*
** Implementácia zásobníku
*/

#include "stack.h"

// Inicializácia zásobníku
void Init(STACK *S)
{
	S->vrchol = 0;
}

// Vloží hodnotu na zásobník
void Push(STACK *S, char z){

  if (S->vrchol==100)
    printf("Chyba: Došlo k pretečeniu zásobníku!\n");
  else {
		S->vrchol++;
		S->data[S->vrchol]=z;
	}
}

// Odstráni znak z vrcholu zásobníku a vráti jeho hodnotu
char TopPop(STACK *S){

	if (S->vrchol==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(-2);
	}
	else {
		return (S->data[S->vrchol--]);
	}
}

// vráti znak z vrcholu zásobníku
char Top(STACK *S){

	if (S->vrchol==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(-2);
	}
	else {
		return (S->data[S->vrchol]);
	}
}

// Odstráni znak z vrcholu zásobníku
void Pop(STACK *S){

	if (S->vrchol==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
	}
	else {
		S->vrchol--;
	}
}

// Vráti počet znakov v zásobníku
int Size(STACK *S){

  return (S->vrchol);
}

// Vráti 1 ak je zásobník prázdny
int Empty(STACK *S){

  return(S->vrchol==0);
}

// Vypíše obsah zásobníku na terminál
void PrintS(STACK *S){
	int i;
	printf("|");
	for(i = 0; i <= S->vrchol; i++){
		printf(" %d |", S->data[i]);
	}
	printf("\n");
}
