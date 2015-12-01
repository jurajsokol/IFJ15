/*
* Projekt: Interpret jazyka IFJ15
* Subor: stack.h
* Popis: Implementácia dátovej štruktúry zásobník
* Autor: Juraj Sokol (xsokol08)
*/

#include "stack.h"
#include "libraries.h"

// Inicializácia zásobníku
void InitS(STACK *S){

	S->data = (int*) malloc(sizeof(int));
	if(S->data == NULL){
		fprintf(stderr, "Memory allocation error!!!\n");
		exit(99);
	}
	S->vrchol = 0;
}

// Vloží hodnotu na zásobník
void PushS(STACK *S, char z){

	S->vrchol++;
	S->data = (int*) realloc(S->data, sizeof(int) * (S->vrchol + 1));
  if (S->data == NULL){
		fprintf(stderr, "Memory allocation error!!!\n");
		exit(99);
	}
  else {
		S->data[S->vrchol]=z;
	}
}

// Odstráni znak z vrcholu zásobníku a vráti jeho hodnotu
int TopPopS(STACK *S){

	if (S->data==NULL)  {
		fprintf(stderr, "data not allocated!!!\n");
		exit(99);
	}
	if(S->vrchol == 0){
		fprintf(stderr, "Podtečenie zásobníku!!!\n");
		exit(99);
	}
	else {
		return (S->data[S->vrchol--]);
		S->data = (int*) realloc(S->data, sizeof(int) * (S->vrchol + 1));
		if (S->data == NULL){
			fprintf(stderr, "Memory allocation error!!!\n");
			exit(99);
		}
	}
}

// vráti znak z vrcholu zásobníku
int TopS(STACK *S){

	if (S->vrchol==0)  {
		fprintf(stderr, "Podtečenie zásobníku!!!\n");
		exit(99);
	}
	else {
		return (S->data[S->vrchol]);
	}
}

// vráti druhý znak z vrcholu zásobníku
int TopSecS(STACK *S){
	if (S->vrchol==0)  {
		fprintf(stderr, "Podtečenie zásobníku!!!\n");
		exit(99);
	}
	else {
		return (S->data[S->vrchol - 1]);
	}
}

// Odstráni znak z vrcholu zásobníku
void PopS(STACK *S){

	if (S->data==NULL)  {
		fprintf(stderr, "data not allocated!!!\n");
		exit(99);
	}
	if (S->vrchol==0)  {
		fprintf(stderr, "Podtečenie zásobníku!!!\n");
		exit(99);
	}
	else {
		S->vrchol--;
		S->data = (int*) realloc(S->data, sizeof(int) * (S->vrchol + 1));
		if (S->data == NULL){
			fprintf(stderr, "Memory allocation error!!!\n");
			exit(99);
		}
	}
}

// Vráti počet znakov v zásobníku
int SizeS(STACK *S){

  return (S->vrchol);
}

// Vráti 1 ak je zásobník prázdny
int EmptyS(STACK *S){

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
