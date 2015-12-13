/*
 * Projekt: Interpret jazyka IFJ15
 * Soubor: variables.c
 * Popis: modul tabulky konstant a proměnných
 * Autor: Lukáš Matula (xmatul26)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "ifj15.h"
#include "variables.h"
#include "scanner.h"

/***
 * struct _TVariable
 *   vlastni typ promene (i konstanty)
 */
struct _TVariable
       {
         TVarType VarType;   // jaky je typ promene/konstanty
         void *VarValue;     // ukazatel na jeji hodnotu (nepracujte primo!)
                             //   (char **, int *, double *)
         PVariable next;     // ukazatel na dalsi prvek
       };


/***
 * VarError()
 *   vypis chyby
 */
void VarError()
{
  printf ("Chyba v práci s tabulkou konstant a proměnných\n");
  exit(10);
}

PConstantTable ConstantsCreate()
{
  PConstantTable table = (PConstantTable)malloc(sizeof(TConstantTable));
  if(table == NULL)
    VarError();
  table->first = NULL;
  return(table);
}


PVariable ConstantsInsert(PConstantTable table, TVarType type, void *value)
{
#ifndef NDEBUG
  if(table == NULL)
    VarError();
#endif
  switch(type)
  {
    case vtUninit:
    {
#ifndef NDEBUG
      VarError();
#endif
    } break;
    case vtInt:
    case vtFloat:
    case vtString:
    {
      PVariable *constant = &(table->first);
      while(*constant != NULL)
      {
        if((*constant)->VarType == type) //pouze jednou vkladame konstantu
        {
          switch(type) //je stejny obsah stejneho typu?
          {
            case vtInt:
            {
              int *new_value = (int *)(value);
              int *cur_value = (int *)((*constant)->VarValue);
              if( (*new_value) == (*cur_value) )
              {
                free(value);
                return(*constant);
              }
            } break;
            case vtFloat:
            {
              double *new_value = (double *)(value);
              double *cur_value = (double *)((*constant)->VarValue);
              if( (*new_value) == (*cur_value) )
              {
                free(value);
                return(*constant);
              }
            } break;
            case vtString:
            {
              char *new_value = (char *)(value);
              char *cur_value = (char *)((*constant)->VarValue);
              if( 0 == strcmp((new_value),(cur_value)) )
              {
                free(value);
                return(*constant);
              }
            } break;
            default:
            {

            }
          }
        }
        constant = &((*constant)->next);
      }
      *constant = (PVariable)malloc(sizeof(TVariable)); //vlozime ji
      if( *constant == NULL)
        VarError();
      (*constant)->VarType = type;
      (*constant)->VarValue = value;
      (*constant)->next = NULL;
      return(*constant);

    } break;
    default:
    {
#ifndef NDEBUG
      VarError();
#endif
    }
  }
#ifndef NDEBUG
  VarError();
#endif
  return(NULL);
}


void ConstantsDestroy(PConstantTable table)
{
#ifndef NDEBUG
  if(table == NULL)
    VarError();
#endif
  PVariable tmp = table->first, tmp2;
  while(tmp != NULL)
  {
    tmp2 = tmp->next;
    free(tmp->VarValue);
    free(tmp);
    tmp = tmp2;
  }
  free(table);
}


PVariableTable VariablesCreate()
{
  PVariableTable table = (PVariableTable)malloc(sizeof(TVariableTable));
  if(table == NULL)
    VarError();
  table->first = NULL;
  return(table);
}


PVariable VariablesInsert(PVariableTable table)
{
#ifndef NDEBUG
  if(table == NULL)
    VarError();
#endif
  PVariable variable = (PVariable)malloc(sizeof(TVariable));
  variable->next = table->first;
  variable->VarType = vtUninit;
  variable->VarValue = NULL;
  table->first = variable;
  return(variable);
}


void VariablesDestroy(PVariableTable table)
{
#ifndef NDEBUG
  if(table == NULL)
    VarError();
#endif
  PVariable tmp = table->first, tmp2;
  while(tmp != NULL)
  {
    tmp2 = tmp->next;
    free(tmp->VarValue);
    free(tmp);
    tmp = tmp2;
  }
  free(table);
}


void VariablesStore(PVariable variable, TVarType type, void *value)
{
#ifndef NDEBUG
  if(variable == NULL)
    VarError();
  if(type == vtUninit)
    VarError();
#endif
  free(variable->VarValue);
  variable->VarType = type;
  variable->VarValue = value;
}


TVarType VariablesGetType(PVariable variable)
{
#ifndef NDEBUG
  if(variable == NULL)
    VarError();
#endif
  return(variable->VarType);
}


void *VariablesGetValue(PVariable variable)
{
#ifndef NDEBUG
  if(variable == NULL)
    VarError();
#endif
  return(variable->VarValue);
}

#ifndef NDEBUG

void ConstantPrint(PVariable constant)
{
  if(constant == NULL)
    VarError();
  switch(constant->VarType)
  {
    case vtInt:
    {
      printf("(int)    ");
      int *i = constant->VarValue;
      printf("%i",*i);
    } break;
    case vtFloat:
    {
      printf("(float)  ");
      double *d = constant->VarValue;
      printf("%g",*d);
    } break;
    case vtString:
    {
      printf("(string) ");
      char *c = constant->VarValue;
      printf("'%s'",c);
    } break;
    case vtUninit:
    {
      printf("(uninit) ERROR");
    } break;
    default:
    {
      printf("(unknown) ERROR");
    }
  }
}
#endif
