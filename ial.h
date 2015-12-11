#ifndef IAL_H_INCLUDED
#define IAL_H_INCLUDED


#include stdio.h
#include stdbool.h
#include malloc.h
#include string.h

typedef struct
{
	char *pole;
	int delka;
}Tquick;

int inic(string *attr, Tquick *sort);

char sort(char ret[],int left,int right);

char QuickSort(char ret[]);

int kmpSearch(Tquick *ret, Tquick *podr, int *vys);

int kmp(string *text, string *param, double *vys);




#endif // IAL_H_INCLUDED
