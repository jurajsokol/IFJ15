/*
 * Projekt: Interpret jazyka IFJ15
 * Soubor: variables.h
 * Popis: modul tabulky konstant a proměnných
 * Autor: Lukáš Matula (xmatul26)
 */

#ifndef VARIABLES_H
#define VARIABLES_H

#include "scanner.h"

/***
 * TVarType
 *   typ promene nebo konstatny pro tabulky konst. a promenych 
 */
typedef enum
        {
          vtInt,     // promena nebo konstanta typu Int
          vtFloat,   // typu Float (double)
          vtString,  // String (char *)
          vtUninit   // neinicializovana
        } TVarType;

/***
 * TVariable
 *   typ konstanty nebo promene pro tabulky konstant a promenych
 *   linearni seznam
 */
typedef struct _TVariable
        TVariable, *PVariable;

/***
 * TConstantTable
 *   vlastni tabulka konstant, vkladani nakonec
 */
typedef struct
        {
          PVariable first;  // ukazatel na prvni prvek, kdyz neni, tak NULL
        } TConstantTable, *PConstantTable;

/***
 * TVariableTable
 *   vlastni tabulka promenych, vkladani na zacatek
 */
typedef struct
        {
          PVariable first;  // ukazatel na prvni prvek, kdyz neni, tak NULL
        } TVariableTable, *PVariableTable;

/***
 * ConstantsCreate()
 *   vytvori tabulku konstant a vrati jeji adresu 
 */
PConstantTable ConstantsCreate();

/***
 * ConstantsInsert()
 *   vlozi prvek do tabulky konstant a vrati ukazatel na nej
 *   1. parametr - tabulka konstant 
 *   2. parametr - typ konstanty
 *   3. parametr - adresa konstanty   
 */
PVariable ConstantsInsert(PConstantTable table, TVarType type, void *value);

/***
 * ConstantsDestroy()
 *   zrusi tabulku konstant i s obsahem
 */
void ConstantsDestroy(PConstantTable table);

/***
 * VariablesCreate()
 *   vytvori tabulku promenych a vrati adresu
 */
PVariableTable VariablesCreate();

/***
 * VariablesInsert()
 *   vlozi prvek do tabulky promenych a vrati ukazatel na nej
 *   promena neni inicializovana
 *   parametr je tabulka promenych
 */
PVariable VariablesInsert(PVariableTable table);

/***
 * VariablesStore()
 *   funkce store (pro semantic, ktera ulozi do promene hodnotu
 *   1. parametr - promena
 *   2. parametr - typ noveho obsahu
 *   3. parametr - hodnota noveho obsahu, přičemž se stará uvolní
 */
void VariablesStore(PVariable variable, TVarType type, void *value);

/***
 * VariablesGetType()
 *    pro semantic
 *   vrati typ promene
 *   parametrem je promena 
 */
TVarType VariablesGetType(PVariable variable);

/***
 * VariablesGetValue()
 *   (pro semantic)
 *   vrati obsah promene
 *   1. parametr - promena 
 */
void *VariablesGetValue(PVariable variable);

/***
 * VariablesDestroy()
 *   zrusi tabulku promenych i s jejim obsahem
 */
void VariablesDestroy(PVariableTable table);

#ifndef NDEBUG
/***
 * ConstantPrint()
 *   vypise typ a obsah konstanty na stdout, ladici funkce
 *   parametr adresa konstanty  
 */
void ConstantPrint(PVariable constant);
#endif

#endif
