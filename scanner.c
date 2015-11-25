/*
* Projekt: Interpret jazyka IFJ15
* Subor: scanner.c
* Popis: Lexikalny analyzator
* Autor: Alexandra Uhrinova (xuhrin01)
*/

#include "scanner.h"
#include "libraries.h"

void TokAddChar(char *tok, int *tokLen, unsigned char c)
{
	(*tokLen)++;
	tok = (char*) realloc(tok, sizeof(char) * (*tokLen));	//realokacia pamate pre dalsi znak
	if(tok == NULL)
	{
		fprintf(stderr, "Memory allocation error!!!\n");
		exit(99);
	}
	tok[(*tokLen - 2)] = c;	//novy znak sa prida na koniec tokenu
	tok[(*tokLen - 1)] = '\0';	//retazec musi obsahovat prazdny znak na konci
}

char *Token(tState *retState, FILE *fp)
{
	int tokLen = 1;	//pociatocna dlzka tokenu
	char *tok = (char*) malloc(sizeof(char));	//alokacia miesta pre prazdny znak
	char znak; 
	tState state = S_START;

	while((znak = getc(fp)) != EOF)
	{		
		switch(state)
		{
			case S_START:
				if(isalpha(znak) || (znak == '_'))		state = S_ID;
				else if(znak == '0')					state = S_ZERO;
				else if(isdigit(znak) && znak != '0')	state = S_NUM;
				else if(znak == '.')					state = S_POINT;
				else if(znak == ':')					state = S_COLON;
				else if(znak == ';')					state = S_SCOL;
				else if(znak == '*')					state = S_MUL;
				else if(znak == '/')					state = S_DIV;
				else if(znak == '+')					state = S_ADD;
				else if(znak == '-')					state = S_SUB;
				else if(znak == '<')					state = S_LOW;
				else if(znak == '>')					state = S_GRE;
				else if(znak == '=')					state = S_EQ;
				else if(znak == '!')					state = S_EXCL;
				else if(znak == '(')					state = S_LRB;
				else if(znak == ')')					state = S_RRB;
				else if(znak == '[')					state = S_LSB;
				else if(znak == ']')					state = S_RSB;
				else if(znak == '{')					state = S_LCB;
				else if(znak == '}')					state = S_RCB;
				else if(znak == '"')					state = S_QUOT;
				else if(isspace(znak))
				{
					state = S_START;
					continue;
				}
				else
				{

					break;	// testovanie - vyskoci sa ak je to zatial neznamy znak
					//	LexError();
				}
				TokAddChar(tok, &tokLen, znak);

			break;

			case S_LOW:
				if(znak == '=')
				{
					TokAddChar(tok, &tokLen, znak);
					*retState = S_LOWEQ;
					return tok;
				}
				else
				{
					ungetc(znak, fp);
					*retState = S_LOW;
					return tok;
				}
			break;

			case S_GRE:
				if(znak == '=')
				{
					TokAddChar(tok, &tokLen, znak);
					*retState = S_GREEQ;
					return tok;
				}
				else
				{
					ungetc(znak, fp);
					*retState = S_GRE;
					return tok;
				}
			break;

			case S_EQ:
				if(znak == '=')
				{
					TokAddChar(tok, &tokLen, znak);
					*retState = S_EQ2;
					return tok;
				}
				else
				{
					ungetc(znak,fp);
					*retState = S_EQ;
					return tok;
				}
			break;

			case S_EXCL:
				if(znak == '=')
				{
					TokAddChar(tok, &tokLen, znak);
					*retState = S_NEQ;
					return tok;
				}
				else
				{
					ungetc(znak, fp);
					*retState = S_EXCL;
					return tok;
				}
			break;

			case S_DIV:
				if(znak == '/')
				{
					state = S_RCOM;
				}
				else if(znak == '*')
				{
					state = S_BCOM;
				}
				else
				{
					ungetc(znak, fp);
					*retState = S_DIV;
					return tok;
				}
			break;

			case S_RCOM:
				if(znak == '\n')
				{
					tok[tokLen-2] = '\0';	// odstranim vlozeny znak '/' z tokenu
					tokLen--;
					state = S_START;
				}
				else
					state = S_RCOM;
			break;

			case S_BCOM:
				if(znak == '*')
					state = S_COMEND;
				else
					state = S_BCOM;
			break;

			case S_COMEND:
				if(znak == '/')
				{
					tok[tokLen-2] = '\0';	// odstranim vlozeny znak '/' z tokenu
					tokLen--;
					state = S_START;
				}
				else
					state = S_BCOM;
			break;

			default:	//pre ucely testovania ignorujem neimplementovane tokeny - case
				state = S_START;
				tok[tokLen-2] = '\0';
				tokLen--;

		}
	}

	*retState = S_EOF;	//vraciam ID tokenu
	return tok;
}

void LexError()
{
	fprintf(stderr, "LEX ERROR\n");
	exit(1);
}
