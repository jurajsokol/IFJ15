/*
* Projekt: Interpret jazyka IFJ15
* Subor: main.c
* Popis: Syntaktický analyzátor
* Autor: Juraj Sokol (xsokol08)
*/

#include "main.h"
#include "stack.h"
#include "scanner.h"
#include "sa_vyrazov.h"

/*
** Funkcia obsahujúca LL tabuľku,
** Vracia číslo pravidla, ktoré sa má použiť
*/
int LL_table(int x, int y){
	int table[5][8] = {
		{0, 0, -1, -1, -1, -1, -1, -1}, // FUNC
		{-1, -1, 1, 2, -1, -1, -1, -1}, // STAT
		{3, 4, -1, -1, -1, -1, -1, -1}, // TYP
		{5, 5, -1, -1, 6, 7, -1, -1}, // ARGS
		{-1, -1, -1, -1, -1, -1, 8, 9}, // ARGS
	};

	switch (y){
		case 33: return table[x - 65][0]; // int
		case 35: return table[x - 65][1]; // string
		case 20: return table[x - 65][2]; // {
		case 34: return table[x - 65][3]; // return
		case 24: return table[x - 65][4]; // ,
		case 17: return table[x - 65][5]; // )
		case 90: return table[x - 65][6]; // exp
		case 3: return table[x - 65][7]; // ;
	}
	/*printf("%d, %d\n", x, y);
	if(y == 33) y = 0; // int
	if(y == 35) y = 1; // string
	if(y == 20) y = 2; // {
	if(y == 34) y = 3; // return
	if(y == 24) y = 4; // ,
	if(y == 17) y = 5; // )
	if(y == 90) y = 6; // VYRAZ
	if(y == 3) y = 7; // ;
	else return -1; // zamedzenie iných čísel (**BUG** segmentation fault)
	printf("%d, %d\n", x - 65, y);

	return table[x - 65][y];*/
	return -1;
}

/*
** Hlavná funkcia syntaktickej analýzy
** vracia či prebehla uspešne a syntaktický strom
** Algoritmus je založený na prediktívnej syntaktickej analýze
*/
int syntakticka_analyza(FILE *fp){
 	unsigned char pravidla[10][7] = {
												{STAT, 17, ARGS, 16, 36, TYP, '\0'}, //0
												{21, STAT, 20, '\0'}, //1
												{3, VYRAZ, 34, '\0'}, //2
												{33, '\0'}, //3
												{35, '\0'}, //4
												{ARGS, 36, TYP, '\0'}, //5
												{ARGS, 36, TYP, 24, '\0'}, //6
												{EPS, '\0'},//7
												{VYRAZ, '\0'}, //8
												{EPS, '\0'}, //9
												};
	STACK zasobnik;
	unsigned int vrchol_z; // znak z vrcholu zásobníku
	tState tokenType; // číslo stavu
	char *vstup;
	int pravidlo, i;

	InitS(&zasobnik);
	PushS(&zasobnik, DOLAR); // na vrchole zásobníku musí byť dolár
	PushS(&zasobnik, FUNC); // dá na zásobník štartujúci neterminál
	vstup = Token(&tokenType, fp); // prečíta prvý token

	while(1){
		PrintS(&zasobnik);
		vrchol_z = TopS(&zasobnik);
		printf("vstup %d\n", tokenType);

		/* Spracovanie výrazov */
		if(vrchol_z == VYRAZ){
			if(analyza(fp, vstup, &tokenType) == 1){
				PopS(&zasobnik);
				continue;
			}
			else{
				return -8;
			}
		}

		/* Epsilonové pravidlo, maže neterminál zo zásobníku */
		if(vrchol_z == EPS){
			PopS(&zasobnik);
			free(vstup);
			continue;
		}

		/* Na vrcholu zásobníku je $ a na vstupu je EOF, syntktická analýza je úspešná */
		if(vrchol_z == DOLAR){
			if(tokenType == 25){ // eof
				FreeS(&zasobnik);
				free(vstup);
				return 1;
			}
			else{
				FreeS(&zasobnik);
				free(vstup);
				return -5;
			}
		}

		/* terminály */
		if(vrchol_z < 64){
			printf("T vstup %d\nvrchol %d\n", tokenType, vrchol_z);
			if(vrchol_z == tokenType){
				PopS(&zasobnik);
				//free(vstup);
				vstup = Token(&tokenType, fp);
				continue;
			}
			else{
				PrintS(&zasobnik);
				printf("vstup %d\n", tokenType);
				FreeS(&zasobnik);
				free(vstup);
				return -6;
			}
		}

		/* neterminály */
		if(vrchol_z > 64){
			printf("LL table %d\n", LL_table(vrchol_z, tokenType));
			if((pravidlo = LL_table(vrchol_z, tokenType)) != -1 ){
				PopS(&zasobnik); // vyberie neterminál
				i = 0;
				while(pravidla[pravidlo][i] != '\0'){ // zapíše pravidlo na zásobník
					PushS(&zasobnik, pravidla[pravidlo][i]);
					i++;
				}
			}
			else{
				FreeS(&zasobnik);
				free(vstup);
				return -7;
			}
		}
	}

	FreeS(&zasobnik);
}

int main(int argc, char *argv[]){
	if(argc == 1) // program je volaný bez argumentov, nemá čo psracovať
		return -1;

	FILE *fp;

	fp = fopen(argv[1],"r");
  	if (fp == NULL)
  	{
    	fprintf(stderr, "Open file error!\n");
    	return -1;
  	}

	printf("%d\n", syntakticka_analyza(fp));

	fclose(fp);

	return 0;
}
