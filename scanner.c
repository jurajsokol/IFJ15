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
				else if(znak == '<')
				{
					TokAddChar(tok, &tokLen, znak);
					*retState = S_WRITE;
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
				else if(znak == '>')
				{
					TokAddChar(tok, &tokLen, znak);
					*retState = S_LOAD;
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

			case S_ID:
				if(isalnum(znak) || znak == '_')
					TokAddChar(tok, &tokLen, znak);
				else
				{
					ungetc(znak, fp);

					if(strcmp(tok, "auto") == 0)
						*retState = S_AUTO;

					else if(strcmp(tok, "cin") == 0)
						*retState = S_CIN;

					else if(strcmp(tok, "count") == 0)
						*retState = S_COUNT;

					else if(strcmp(tok, "double") == 0)
						*retState = S_DOUB;

					else if(strcmp(tok, "else") == 0)
						*retState = S_ELSE;

					else if(strcmp(tok, "for") == 0)
						*retState = S_FOR;

					else if(strcmp(tok, "if") == 0)
						*retState = S_IF;

					else if(strcmp(tok, "int") == 0)
						*retState = S_INT;

					else if(strcmp(tok, "return") == 0)
						*retState = S_RET;

					else if(strcmp(tok, "string") == 0)
						*retState = S_STR;

					else 
						*retState = S_ID;

					return tok;
				}
			break;

			case S_QUOT:
				if(znak == '"')
				{
					TokAddChar(tok, &tokLen, znak);
					*retState = S_RETAZ;
					return tok;
				}
				else if(znak == '\\')
				{
					state = S_ESC;
					TokAddChar(tok, &tokLen, znak);
				}
				else
					TokAddChar(tok, &tokLen, znak);
			break;

			case S_ESC:
				TokAddChar(tok, &tokLen, znak);
				state = S_QUOT;
			break;

			case S_NUM:
				if(znak == '.')
				{
					state = S_FLOAT;
					TokAddChar(tok, &tokLen, znak);
				}
				else if(isdigit(znak))
					TokAddChar(tok, &tokLen, znak);
				// else if(znak == 'e' || znak == 'E')
				// {
				// 	TokAddChar(tok, &tokLen, znak);
				// 	state = S_EXP;
				// }
				else
				{
					ungetc(znak, fp);
					*retState = S_NUM;
					return tok;
				}
			break;

/*			case S_EXP:
				if(znak == '-' || znak == '+')
				{
					TokAddChar(tok, &tokLen, znak);
				}
				else if(isdigit(znak))
				{
					TokAddChar(tok, &tokLen, znak);
					state = S_NUM;
				}
			break;
*/
			case S_FLOAT:
				if(isdigit(znak))
					TokAddChar(tok, &tokLen, znak);
				// else if(znak == 'e' || znak == 'E')
				// {
				// 	TokAddChar(tok, &tokLen, znak);
				// 	state = S_EXP2;
				// }
				else
				{
					ungetc(znak, fp);
					*retState = S_FLOAT;
					return tok;
				}
			break;

			case S_COLON:
				if(znak == ':')
				{
					TokAddChar(tok, &tokLen, znak);
					*retState = S_SCOPE;
					return tok;
				}
				else
				{
					ungetc(znak, fp);
					*retState = S_COLON;
					return tok;
				}
			break;

			case S_POINT:
			case S_SCOL:
			case S_MUL:
			case S_ADD:
			case S_SUB:
			case S_LRB:
			case S_RRB:
			case S_LSB:
			case S_RSB:
			case S_LCB:
			case S_RCB:
			{
				ungetc(znak, fp);
				*retState = state;
				return tok;
			}
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
