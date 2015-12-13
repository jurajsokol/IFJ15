/*
* Projekt: Interpret jazyka IFJ15
* Soubor: ial.c
* Popis: Funkce pro pøedmìt IAL
* Autor: Stepan Smolka (xsmolk02), Juraj Sokol (xsokol08)
*/


#include "ial.h"


int inic(string *attr, Tquick *sort)
{
    sort->pole = malloc(((attr->length+1)*sizeof(char)));

	sort->delka = ((attr->length)-1);
	if ((sort->pole) == NULL)
		return 1;
	for (int i = 0; i <= sort->delka; i++)
		sort->pole[i] = attr->str[i];
	return 0;
}


char sort(char ret[],int left,int right)
{
    char tex;
    if(left<right)
    {
        int pom = left;
        for (int i =left+1;i<right;i++)
        {
            if (ret[i]>ret[left])
            {
                pom++;
                tex=ret[pom];
                ret[pom]=ret[i];
                ret[i]=tex;

            }
        }
     tex=ret[pom];
     ret[pom]=ret[left];
     ret[left]=tex;

   sort(ret,left,pom);
   sort(ret,pom+1,right);
    }
}
/* Quick sort */
char QuickSort(char ret[])
{
    char tex;
    int left=0;
    int right=strlen(ret);
    int i;

    if(left<right)
    {
        int pom = left;
        for (i =left+1;i<right;i++)
        {
            if (ret[i]>ret[left])
            {
                pom++;
                tex=ret[pom];
                ret[pom]=ret[i];
                ret[i]=tex;
            }
        }
     tex=ret[pom];
     ret[pom]=ret[left];
     ret[left]=tex;

   sort(ret,left,pom);
   sort(ret,pom+1,right);
    }
}
}


/* Vyhledavaci algoritmus */
int kmpSearch(Tquick *ret, Tquick *podr, int *vys);
{
    int r=0;
    int p=0;
    int *vec,m,n;

    vec=malloc((ret->delka+podr->delka)*sizeof(int));
    if (vec==NULL)
        return 0;

    vec[0]=-1;

    for(m=1; k<=podr->delka;k++)
    {
        n=vec[m-1];
        while(n>0&&podr->pole[n != podr->pole[m-1])
            n=ven[n];
        vec[m]=n+1;
    }

    //KMP algoritmus

    while(r<=ret->delka && p<=podr->delka)
    {
        if (p==-1 || (ret->pole[r])==(podr->[p]))
        {
            r++;
            p++;
        }
        else
            p=vec[p];
    }
    free(vec);

}
/* Zpracovani vstupniho retezce */
int kmp(string *text, string *param, double *vys)
{
    int pom1,pom2;

    pom1=0;
    pom2=0;

    Tquick ret =
    {
        .pole=NULL,
        .delka=0
    };

    if(inic(text,&ret)==1)
        return 1;

    Tquick podret =
    {
        .pole=NULL,
        .delka=0
    };

    if(inic(param,&podret)==1)
    {
        free(ret.pole);
        return 1;
    }

    if((pom1=kmpSearch(&ret,&podret,&pom2)) <= ((ret.delka)+1))
        *vys=pom1;
    else
        *vys=-1;

    free(ret.pole);
    free(podret.pole);

    if (pom2!=0)
        return pom2;

    return 0;
}

int length(char *s){
  int l = 0;

  while(s[l] != '\0'){
    l++;
  }
  return l;
}

char *substr(char *s , int i , int n ){
  char *sub;
  int j = 0;
  int k = i + n;
  if(n != 0){
    sub = (char*) malloc(sizeof(char)*(n+1));
    for(; i<k; i++){
      sub[j] = s[i];
      j++;
    }
    sub[i] = '\0';
	  return sub;
  }
	return "";
}

char *concat(char *s1 , char *s2 ){
	char *con;
	int i = 0;
	int j = 0;
	con = (char*) malloc(sizeof(char));

	while(s1[i] != '\0'){
		con[i] = s1[i];
		i++;
		con = realloc(con, sizeof(char)*(i+1));
	}
	while(s2[j] != '\0'){
		con[i] = s2[j];
		i++;
		j++;
		con = realloc(con, sizeof(char)*(i+1));
	}
	con[i] = '\0';
	return con;
}
