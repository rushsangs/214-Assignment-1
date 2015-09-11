/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char *contents;
	char *tokentype;
	struct TokenizerT_ *next;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
	printf("In Create: %s \n", ts);
	
	int i;
	int start=0;
	int end=0;
	TokenizerT *words = (struct TokenizerT_ *)malloc(sizeof(struct TokenizerT_));
	words->contents=(char *)(malloc(sizeof(char)*5));
	TokenizerT *head = words;
	for(i=0;i<strlen(ts);i++)
	{
		//printf("current char: %c\n", ts[i]); //this outputs spaces as well
		//if(isspace(ts[i])==0)
		//{
			if(isalpha(ts[i]))
			{
				printf("%c\n", ts[i]);	
				int g = 0;
				words->tokentype="WORD";
				while(isalpha(ts[i]))
				{
					//printf("char %c\n", ts[i]);
					words->contents[g]=ts[i];
					g++;
					if(g >= 5)
					{
						//printf("in");
						words->contents=realloc(words->contents, g*sizeof(char));
					}
					//printf("out");
					i++;
				}
				words->next=(struct TokenizerT_ *)malloc(sizeof(struct TokenizerT_));
				//printf("contents=%s\n", words->contents);
				words=words->next;
				words->contents=(char *)(malloc(sizeof(char)*5));
				
			}
			else if(isdigit(ts[i]))
			{ 
				//make an ishex function
				//if(isxdigit(ts[i]))
				if(ts[i]=='0' && ts[i+1]=='x' && (isdigit(ts[i+2]) || ('a'<=ts[i+2] && ts[i+2]<='f') || ('A'<=ts[i+2] && ts[i+2]<='F')))
					{
						words->tokentype="HEXADECIMAL";
						int g = 2;
						i=i+2;
						words->contents[0]='0';
						words->contents[1]='x';
						while(isxdigit(ts[i]))
						//while(isdigit(ts[i])!=0 || ('a'<=ts[i] && ts[i]<='f') || ('A'<=ts[i] && ts[i]<='F'))
						{
							words->contents[g]=ts[i];
							g++;
							if(g>=5)
								words->contents=realloc(words->contents, g*sizeof(char));
							i++;		
						}
						words->next=(struct TokenizerT_ *)malloc(sizeof(struct TokenizerT_));
						words=words->next;
						words->contents=(char *)(malloc(sizeof(char)*5));	
						i--;
					}
				else if(ts[i]=='0' && '0'<= ts[i+1] && ts[i+1] <= '7')
					{
						words->tokentype="OCTAL";
						int g = 0;
						while('0'<=ts[i] && ts[i]<='7')
						{
							words->contents[g]=ts[i];
							g++;
							i++;
							if(g>=5)
								words->contents=realloc(words->contents, g*sizeof(char));
						}
						words->next=(struct TokenizerT_ *)malloc(sizeof(struct TokenizerT_));
						words=words->next;
						words->contents=(char *)(malloc(sizeof(char)*5));
						i--;
					}
				else if(ts[i+1]=='.' || ts[i+1]=='e' || ts[i+1] == 'E');
					{
						/*words->tokentype="FLOATING";
						int g = 2;
						words->contents[0]=ts[i];
						words->contents[1]=ts[i+1];
						while(isdigit(ts[i]) || ts[i]=='e' ||)
						{
							
						}*/
					}
				else
					{
						words->tokentype="DIGIT";
						int g = 0;
						while(isdigit(ts[i]))
						{
							words->contents[g]=ts[i];
							g++;
							i++;
							if((ts[i]=='0' && ( ts[i]=='x' || ('0'<=ts[i] && ts[i] <= '7'))))
								break;	
							if(g>=5)
								words->contents=realloc(words->contents, g*sizeof(char));		
						}
						words->next=(struct TokenizerT_ *)malloc(sizeof(struct TokenizerT_));
						words=words->next;
						words->contents=(char *)(malloc(sizeof(char)*5));
						i--;
					}	
			}

	//	}
	}
	return head;
 	 //return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {

  return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	
	printf("Input: %s \n", argv[1]);
	TokenizerT *tokens = TKCreate(argv[1]);
	
	while(tokens!=NULL)
	{
		printf("INMAIN: %s \t %s\n", tokens->contents,tokens->tokentype);
		tokens=tokens->next;
	}	
  	return 0;


}
