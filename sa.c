/*
* Projekt: Interpret jazyka IFJ15
* Subor: main.c
* Popis: Syntaktický analyzátor
* Autor: Juraj Sokol (xsokol08)
*/

#include "sa.h"
#include "stack.h"
#include "scanner.h"
#include "sa_vyrazov.h"

/*
** Funkcia obsahujúca LL tabuľku,
** Vracia číslo pravidla, ktoré sa má použiť
*/
int LL_table(int x, int y){
	int table[14][26] = {
		{1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, 28, -1, -1, -1, -1}, // FUNC
		{2, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30}, // TYP
		{4, 4, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1. -1, -1}, // ARG
		{9, 9, -1, -1, 6, 7, 8, 10, 11, 12, 13, -1, -1, -1, 0, -1, -1, 0, -1, 0, -1, -1, -1, -1, -1, 9}, // STAT
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, -1, -1, 15, -1}, // ID
		{16, 16, 17, -1, -1, -1, 34, -1, -1, -1, -1, 18, 19, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16}, // DEC
		{-1, -1, 0, 0, -1, -1, 20, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, 20, -1, 20, -1, -1, -1, -1, -1}, // EXP
		{0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 22, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1}, // ELSE
		{-1, -1, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, 0, -1, 23, -1, -1, -1, -1, -1, -1, -1, 31, -1, -1}, // CIN
		{-1, -1, -1, -1, -1, -1, 34, -1, -1, -1, -1, -1, -1, 0, -1, -1, 24, -1, -1, -1, -1, -1, -1, 33, -1, -1}, // COUT
		{-1, -1, 26, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1}, // ARGSF
		{-1, -1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, // ARGS
		{-1, -1, -1, -1, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, // BODY
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, 30, -1, -1}, // INCL
	};

	switch (y){
		case 33: return table[x - 65][0]; // int
		case 35: return table[x - 65][1]; // string
		case 24: return table[x - 65][2]; // ,
		case 17: return table[x - 65][3]; // )
		case 20: return table[x - 65][4]; // {
		case 34: return table[x - 65][5]; // return
		case 36: return table[x - 65][6]; // id
		case 32: return table[x - 65][7]; // if
		case 31: return table[x - 65][8]; // for
		case 27: return table[x - 65][9]; // cin
		case 28: return table[x - 65][10]; // COUT
		case 12: return table[x - 65][11]; // =
		case 18: return table[x - 65][12]; // [
		case 3: return table[x - 65][13]; // ;
		case 30: return table[x - 65][14]; // else
		case 46: return table[x - 65][15]; // >>
		case 47: return table[x - 65][16]; // <<
		case 25: return table[x - 65][17]; // EOF
		case 37: return table[x - 65][18]; // VYRAZ, cislo
		case 21: return table[x - 65][19]; // }
		case 16: return table[x - 65][20]; // (
		case 23: return table[x - 65][21]; // #
		case 8: return table[x - 65][22]; // <
		case 42: return table[x - 65][23]; // string
		case 1: return table[x - 65][24]; // .
		case 26: return table[x - 65][25]; // auto
	}

	return -2;
}

/*
** Hlavná funkcia syntaktickej analýzy
** vracia či prebehla uspešne a syntaktický strom
** Algoritmus je založený na prediktívnej syntaktickej analýze
*/
int syntakticka_analyza(FILE *fp){
 	unsigned char pravidla[35][11] = {
												{EPS, '\0'},
												{FUNC, BODY, 17, ARG, 16, 36, TYP, '\0'}, //1
												{33, '\0'}, //2
												{35, '\0'}, //3
												{ARGS, 36, TYP, '\0'}, //4
												{ARGS, 36, TYP, 24, '\0'}, //5
												{STAT, 21, STAT, 20, '\0'}, //6
												{STAT, 3, EXP, 34, '\0'}, //7
												{STAT, 3, ID, 36, '\0'},//8
												{STAT, 3, DEC, '\0'}, //9
												{ELSE, STAT, 17, EXP, 16, 32, '\0'}, //10
												{STAT, 17, ID, 36, 3, EXP, 3, DEC, 16, 31, '\0'}, //11
												{STAT, 3, CIN, 46, 27, '\0'}, //12
												{STAT, 3, COUT, 47, 28, '\0'}, //13
												{VYRAZ, 12, '\0'}, //14
												{17, VYRAZ, 16, 36, 1, '\0'}, //15
												{DEC, 36, TYP, '\0'}, //16
												{DEC, 36, 24, '\0'}, //17
												{DEC, EXP, 12 ,'\0'}, //18
												{DEC, 19, EXP, 18, '\0'}, //19
												{VYRAZ, '\0'}, //20
												{17, VYRAZ, 16, '\0'}, //21
												{STAT, 30, '\0'}, //22
												{CIN, 46, '\0'}, //23
												{COUT, 47, '\0'}, //24
												{ARGSF, EXP, '\0'}, //25
												{ARGSF, 24, '\0'}, //26
												{21, STAT, 20, '\0'}, // 27
												{INCL, 36, 23, '\0'}, // 28
												{FUNC, 9, 36, 1, 36, 8, '\0'}, // 29
												{26, '\0'}, // 30
												{CIN, 42, '\0'}, // 31
												{CIN, 36, '\0'}, // 32
												{COUT, 42, '\0'}, // 33
												{COUT, 36, '\0'}, // 34
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
		vrchol_z = TopS(&zasobnik);

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
			//FreeToken(vstup);
			continue;
		}

		/* Na vrcholu zásobníku je $ a na vstupu je EOF, syntktická analýza je úspešná */
		if(vrchol_z == DOLAR){
			if(tokenType == 25){ // eof
				FreeS(&zasobnik);
				//FreeToken(vstup);
				printf("\n");
				return 1;
			}
			if(tokenType == 33) // int
				PushS(&zasobnik, FUNC);
			else{
				FreeS(&zasobnik);
				//FreeToken(vstup);
				return -5;
			}
		}

		/* terminály */
		if(vrchol_z < 64){
			if(vrchol_z == tokenType){
				PopS(&zasobnik);
				//FreeToken(vstup);
				vstup = Token(&tokenType, fp);
				continue;
			}
			else{
				FreeS(&zasobnik);
				//FreeToken(vstup);
				return -6;
			}
		}

		/* neterminály */
		if(vrchol_z > 64){
			if((pravidlo = LL_table(vrchol_z, tokenType)) != -1 ){
				printf("%d ,", pravidlo);
				PopS(&zasobnik); // vyberie neterminál
				i = 0;
				while(pravidla[pravidlo][i] != '\0'){ // zapíše pravidlo na zásobník
					PushS(&zasobnik, pravidla[pravidlo][i]);
					i++;
				}
			}
			else{
				FreeS(&zasobnik);
				//FreeToken(vstup);
				return -7;
			}
		}
	}

	FreeS(&zasobnik);
}
