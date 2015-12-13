/*
* Projekt: Interpret jazyka IFJ15
* Subor: sa_vyrazov.c
* Popis: Syntaktický analyzátor výrazov
* Autor: Juraj Sokol (xsokol08)
*/

#include "sa_vyrazov.h"
#include "stack.h"
#include "scanner.h" // obsahuje enum štruktúru znakov
#include "libraries.h"

/*
** pomocná funkcia pre hľadanie v precedenčnej tabuľke a v pravidlách
*/
int dekoder(int tType){
	if(tType == 3 || tType == 20 || tType == 46 || tType == 47){ // stav ;, {
		return 13;
	}
	if(tType == 24){ // ,
		return 14;
	}
	if(tType < 12){ // znaky *, /, +, -, <, >, <=, >=
		return tType - 4;
	}
	if(tType < 15){ // zanky ==, !=
		return tType - 5;
	}
	if(tType < 18){
		return tType - 6; // znaky ( a )
	}
	if(tType == 37){ // identifikátor alebo id
		return 12;
	}
	if(tType == DOLAR){
		return 13;
	}
	return 0;
}

/*
** Funkcia obsahujúca precedenčnú tabuľku
*/
char precedencna_tabulka(int t_x, int t_y){
	char tabulka[15][15] = { //| * | / | + | - | < | > | <=| >=| ==| !=| ( | ) | i | $ | , |
														 {'>','>','>','>','>','>','>','>','>','>','<','>','<','>','>'}, // *
														 {'>','>','>','>','>','>','<','>','<','>','<','>','<','>','>'}, // /
														 {'<','<','>','>','>','>','<','>','<','>','<','>','<','>','>'}, // +
										 				 {'<','<','>','>','>','>','>','>','X','>','<','>','<','>','>'}, // -
														 {'<','<','<','<','>','>','>','>','<','>','<','>','<','>','>'}, // <
														 {'<','<','<','<','>','>','>','>','<','>','<','>','<','>','>'}, // >
														 {'<','<','<','<','>','>','>','>','<','>','<','>','<','>','>'}, // <=
														 {'<','<','<','<','>','>','>','>','<','>','<','>','<','>','>'}, // >=
														 {'<','<','<','<','>','>','>','>','X','>','<','>','<','>','>'}, // ==
														 {'<','<','<','<','>','>','<','>','<','>','<','>','<','>','>'}, // !=
														 {'<','<','<','<','<','<','<','<','<','<','<','=','<','X','<'}, // (
														 {'>','>','>','>','>','>','<','>','<','>','X','>','X','>','>'}, // )
														 {'>','>','>','>','>','>','>','>','>','>','=','>','X','>','>'}, // i
														 {'<','<','<','<','<','<','<','<','<','<','<','U','<','U','<'}, // $
														 {'<','<','<','<','<','<','<','<','<','<','<','>','<','X','>'}, // ,

													};
	printf("Table %d, %d\n", dekoder(t_x), dekoder(t_y));
	return tabulka[dekoder(t_x)][dekoder(t_y)];
}

/*
** Hlavná funkcia syntaktickej analýzy, simuluje vytváranie derivačného stromu
*/
int analyza(FILE *fp, char *vstup, tState *tokenType){
	char pravidla[16][6] = { // čísla sú z enum štruktúry v scanner.h
										{E, 4, E, -1, '\0'}, // *
										{E, 5, E, -1, '\0'}, // /
										{E, 6, E, -1, '\0'}, // +
										{E, 7, E, -1, '\0'}, // -
										{E, 8, E, -1, '\0'}, // <
										{E, 9, E, -1, '\0'}, // >
										{E, 10, E, -1, '\0'}, // <=
										{E, 11, E, -1, '\0'}, // >=
										{E, 13, E, -1, '\0'}, // ==
										{E, 14, E, -1, '\0'}, // !=
										{17, E, 16, -1, '\0'}, // zátvorky ()
										{E, 7, -1, '\0'}, // záporné číslo
										{37, -1, '\0'}, // cislo alebo identifikátor
										{E, 24, E, -1, '\0'}, // argumenty funkcie
										{17, E, 16, 37, -1, '\0'} // funkcia
									}; // 60 je $
	char vyraz[5]; // výraz sa bude porovnávať s tabuľkou
	STACK zasobnik;
	char znak; // znak zo vstupu a zo zásobníku
	int i;

printf("SAV **************\n");
	InitS(&zasobnik); // inicializácia zásobniku

	PushS(&zasobnik, DOLAR); //na vrcholu zásobniku musí byť $

	do{
		znak = TopS(&zasobnik);
		if(znak == E){ //nemôže porovnávať s neterminálom, preto vyberie zo zásobníku druhý znak
			znak = TopSecS(&zasobnik);
		}

		//if(token T)

		if(*tokenType == 36 || *tokenType == 42){ // zmeni id na cislo
			*tokenType = 37;
		}

		/*pomocné ladiace funkcie*/
		printf("SAV **************\n");
		PrintS(&zasobnik);
		printf("SAV znak = %d\n", znak);
		printf("SAV vstup = %d\n******************\n", *tokenType);
		/** *********************** */
		printf("PT: %c\n", precedencna_tabulka(znak, *tokenType));
		switch(precedencna_tabulka(znak, *tokenType)){

			case '=':
				PushS(&zasobnik, *tokenType);
				//FreeToken(vstup);
				vstup = Token(tokenType, fp);
				continue;

			case '<':
				if(TopS(&zasobnik) == E){
					PopS(&zasobnik);
					PushS(&zasobnik, -1);
					PushS(&zasobnik, E);
					PushS(&zasobnik, *tokenType);
				}
				else{
					PushS(&zasobnik, -1); // -1 je <
					PushS(&zasobnik, *tokenType);
				}
				//FreeToken(vstup);
				vstup = Token(tokenType, fp);
				continue;

			case '>':

				/* Vyberie zo zásobníku znaky a vloží do premennej výraz */
				i = 0;
				do{
					vyraz[i] = TopPopS(&zasobnik);
					i++;
				}while(vyraz[i - 1] != -1);
				vyraz[i] = '\0';

				/* Porovnáva výraz s pravidlami */
				for(i = 0; i<=16; i++){
					if(i == 16){ // nenašla sa zhoda
						FreeS(&zasobnik);
						SAError();
					}
					if(strcmp(pravidla[i], vyraz) == 0){ // našla sa zhoda
						break;
					}
				}

					PushS(&zasobnik, E); // Pushne neterminál na zásobník
					continue;

			case 'U': // výraz je správny
				FreeS(&zasobnik);
				return 0;
			case 'X': // chyba
				FreeS(&zasobnik);
				SAError();
			}
		}while(1);

	FreeS(&zasobnik);
	return 0;
}

void FreeToken(char *vstup){
	if(vstup != NULL){
			free(vstup);
			vstup = NULL;
	}
}

void SAError()
{
	fprintf(stderr, "SYNTAX ERROR\n");
	exit(2);
}
