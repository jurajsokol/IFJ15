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
	static int typ = 0;
	if(tType == -1){
		return typ;
	}
	if(tType == 3){ // stav ;
		return 13;
	}
	if(tType == E){ // neterminál, nevyhľadáva sa v tabuľke
		return typ;
	}
	if(tType == 16){ // neterminál, nevyhľadáva sa v tabuľke
		return 10;
	}
	if(tType < 12){ // znaky *, /, +, -, <, >, <=, >=
		typ = tType - 4;
		return typ;
	}
	if(tType < 15){ // zanky ==, !=
		typ = tType - 5;
		return typ;
	}
	if(tType < 18){
		typ = tType - 6;
		return typ; // znaky ( a )
	}
	if(tType == 37){ // identifikátor
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
	char tabulka[14][14] = { //| * | / | + | - | < | > | <=| >=| ==| !=| ( | ) | i | $ |
														 {'>','>','>','>','>','>','>','>','>','>','<','>','<','>'}, // *
														 {'>','>','>','>','>','>','<','>','<','>','<','>','<','>'}, // /
														 {'<','<','>','>','>','>','<','>','<','>','<','>','<','>'}, // +
										 				 {'<','<','>','>','>','>','>','>','X','>','<','>','<','>'}, // -
														 {'<','<','<','<','>','>','>','>','<','>','<','>','<','>'}, // <
														 {'<','<','<','<','>','>','>','>','<','>','<','>','<','>'}, // >
														 {'<','<','<','<','>','>','>','>','<','>','<','>','<','>'}, // <=
														 {'<','<','<','<','>','>','>','>','<','>','<','>','<','>'}, // >=
														 {'<','<','<','<','>','>','>','>','X','>','<','>','<','>'}, // ==
														 {'<','<','<','<','>','>','<','>','<','>','<','>','<','>'}, // !=
														 {'<','<','<','<','<','<','<','<','<','<','<','=','<','X'}, // (
														 {'>','>','>','>','>','>','<','>','<','>','X','>','X','>'}, // )
														 {'>','>','>','>','>','>','<','>','<','>','X','>','X','>'}, // i
														 {'<','<','<','<','<','<','<','<','<','<','<','X','<','X'}, // $
													};

	printf("Precedenčná tabuľka: %d, %d, %c\n", dekoder(t_x), dekoder(t_y), tabulka[dekoder(t_x)][dekoder(t_y)]);
	return tabulka[dekoder(t_x)][dekoder(t_y)];
}

/*
** Hlavná funkcia syntaktickej analýzy, simuluje vytváranie derivačného stromu
*/
int analyza(FILE *fp, char *vystup){
	int pravidla[13][4] = { // čísla sú z enum štruktúry v scanner.h
										{E, 4, E, -1}, // *
										{E, 5, E, -1}, // /
										{E, 6, E, -1}, // +
										{E, 7, E, -1}, // -
										{E, 8, E, -1}, // <
										{E, 9, E, -1}, // >
										{E, 10, E, -1}, // <=
										{E, 11, E, -1}, // >=
										{E, 13, E, -1}, // ==
										{E, 14, E, -1}, // !=
										{17, E, 16, -1}, // zátvorky ()
										{17, E, 16, -1}, // -- II --
										{37, -1}, // identifikátor
									}; // 60 je $

	STACK zasobnik;
	char *vstup;
	char znak; // znak zo vstupu a zo zásobníku
	tState tokenType; // číslo stavu
	int y = 0; // pomocná premenná pre tabuľku pravidiel

	Init(&zasobnik); // inicializácia zásobniku

	Push(&zasobnik, DOLAR); //na vrcholu zásobniku musí byť $
	vstup = Token(&tokenType, fp); // načíta prvý znek zo vstupu

	do{
		znak = Top(&zasobnik);
		if(znak == E){ //nemôže porovnávať s neterminálom, preto vyberie zo zásobníku druhý znak
			znak = TopSec(&zasobnik);
		}

		/* pomocné ladiace funkcie */
		PrintS(&zasobnik);
		printf("znak = %d\n", znak);
		printf("vstup = %d\n", tokenType);
		/* *********************** */

		switch(precedencna_tabulka(znak, tokenType)){
			case '=':
				Push(&zasobnik, tokenType);
				continue;
			case '<':
				if(Top(&zasobnik) == E){
					Pop(&zasobnik);
					Push(&zasobnik, -1);
					Push(&zasobnik, E);
					Push(&zasobnik, tokenType);
				}
				else{
					Push(&zasobnik, -1); // -1 je <
					Push(&zasobnik, tokenType);
				}
				free(vstup);
				vstup = Token(&tokenType, fp);
				continue;
			case '>':
				znak = TopPop(&zasobnik);
				do{ // kontroluje zásobník s pravidlami
					printf("znak %d\n", znak);
					printf("tabulka %d, %d\n", pravidla[dekoder(znak)][y], dekoder(znak));
					if(znak == pravidla[dekoder(znak)][y]){  // znak sa rovná s časťou niektorého pravidla
						y++;
						znak = TopPop(&zasobnik); // vyberie zo zásobníku ďalší znak
							PrintS(&zasobnik);
					}
					else{ // ERROR
						PrintS(&zasobnik);
						printf("znak = %d\n", znak);
						return -2;
					}
				}while(znak != -1);

				if(Top(&zasobnik) == DOLAR){ // úspech
					switch (tokenType) { // ak je za výrazom ; alebo ), tak je správny
						case 3: // ;
							FreeS(&zasobnik);
							vystup = vstup;
							return 1;
						default:	// ukončí slučku
							znak = -1;
					}
				}

					Push(&zasobnik, E); // Pushne neterminál na zásobník
					y = 0;
					continue;

			case 'X': // chyba
				PrintS(&zasobnik);
				return -5;
			}

	}while(Size(&zasobnik)); // opakuje, pokiaľ nebude na vrcholu zásobníku $

	return 0;
}
