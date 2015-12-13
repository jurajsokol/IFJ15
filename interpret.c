/*
* Projekt: Interpret jazyka IFJ15
* Subor: interpret.c
* Popis: Interpret
* Autor: Rennerová Jindřiška (xrenne00)
*/

#include "libraries.h"
#include "interpret.h"



int inter(MainData * data, tListOfInstr * instrList)
{
    listFirst(instrList);
    tInstr *instr;
    while (1)
    {
        instr = listGetData(ilist);         //vytáhnu instrukci
        if(instr == NULL)
            return internalError();
        TVarData *param1, *param2, *param3;
        int result;
        switch(instr->type)
        {
            /*******Aritmetické operace*******/

            case I_ADD:
                if((param2->type==tDouble) && (param3->type==tDouble))
                {
                    param1->type = tDouble;
                    param1->tDouble = param2->tDouble + param3->tDouble;
                }
                else if ((param2->type==tInteger) && (param3->type==tInteger))
                {
                    param1->type = tInteger;
                    param1->tInteger = param2->tInteger + param3->tInteger;
                }
                else if ((param2->type==tDouble) && (param3->type==tInteger))
                {
                    param1->type = tInteger;
                    param1->tInteger = param2->tDouble + param3->tInteger;
                }
                else if ((param2->type==tInteger) && (param3->type==tDouble))
                {
                    param1->type = tInteger;
                    param1->tInteger = param2->tInteger + param3->tDouble;
                }
                else return INTERPRET_ERR;
                break;

        }
    }
}
