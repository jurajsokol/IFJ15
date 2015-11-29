/*
* Projekt: Interpret jazyka IFJ15
* Subor: stack.h
* Popis: Implementácia dátovej štruktúry zásobník
* Autor: Juraj Sokol (xsokol08)
*/

#include "stack.h"
#include "libraries.h"

// Inicializácia zásobníku
void Init(STACK *S)
{
	S->data = (int*) malloc(sizeof(int));
	S->vrchol = 0;
}

// Vloží hodnotu na zásobník
void Push(STACK *S, char z){
	S->vrchol++;
	S->data = (int*) realloc(S->data, sizeof(int) * (S->vrchol + 1));
  if (S->data == NULL)
    printf("Chyba: Došlo k pretečeniu zásobníku!\n");
  else {
		S->data[S->vrchol]=z;
	}
}

// Odstráni znak z vrcholu zásobníku a vráti jeho hodnotu
int TopPop(STACK *S){

	if (S->data==NULL)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(-2);
	}
	else {
		return (S->data[S->vrchol--]);
		S->data = (int*) realloc(S->data, sizeof(int) * (S->vrchol + 1));
	}
}

// vráti znak z vrcholu zásobníku
int Top(STACK *S){

	if (S->vrchol==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(-2);
	}
	else {
		return (S->data[S->vrchol]);
	}
}

// vráti druhý znak z vrcholu zásobníku
int TopSec(STACK *S){
	if (S->vrchol==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(-2);
	}
	else {
		return (S->data[S->vrchol - 1]);
	}
}

// Odstráni znak z vrcholu zásobníku
void Pop(STACK *S){

	if (S->data==NULL)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
	}
	else {
		S->vrchol--;
		S->data = (int*) realloc(S->data, sizeof(int) * (S->vrchol + 1));
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

void FreeS(STACK *S){
	free(S->data);
}
