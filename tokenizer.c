/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char *tokentype(char *token);

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

/*NOTES FOR ETHAN
 * Hey Ethan,
 * I've made a lot of changes to the code. I'll talk about them mostly here.
 *The new structure is not a linked list of Tokenizer Objects, it's simply one Tokenizer object which holds the following:
 * 	-The entire string is stored, since the description for TKCreate is that it should copy the string.
 * 	- The currentPos is an integer that stores the current position that we are in the string. Useful for finding tokens.
 * 	- tstate: this is an enum, which is kind of optional. We might not need it in the Tokenizer object.
 *
 * How it would work
 * 	-We create a tokenizer struct in TKCreate, simply initialize the string part.
 * 	-The TKGetNextToken will simply use the Tokenizer and return the word itself. (This is what the problem describes afterall.)
 * 	-In Main, we get the token from TKGetNextToken and pass it to a new function which will determine what exactly type this token is:
 * 		-word
 * 		-hexadecimal
 * 		-float and so on. This is where your code should come in, you would need to implement it in another function and we call it.
 * 	-The new function will make use of the TokenizerState enum and this way we can traverse through the entire FSM easily. The new function will finally return thr type of the token and we can print it along in the main function.
 *
 * What needs to be done:
 * 	- You can make changes or suggestions however you want, and probably add them in another comment for me.
 * 	- The isalpha code would fit in as it is, with just changing the names of the variables a little bit (Let me know if you can't figure it out, I'll tell you what's what.)
 * 	- The code for numbers however, will need to be changed to make it work with the ENUM so yeah. I intend to draw the entire FSM with the enums and send it over to you/ post on github so you can see what I meant and probably put in your own suggestions.
 * 	-Still need to invoke the destroy and use it to destroy all the dynamic variables. You could work on that too!
 */

/*  Enum declaration
*  Each state should stand for one circle in the FSM Brian provided. TBD 
*/

enum TokenizerState{
		INIT,
		TS_STATE0,					//different states as in the FSM
		TS_STATE1,
		TS_STATE2,
		TS_STATE3,
		TS_STATE4,
		TS_STATE5,
		TS_STATE6,
		TS_STATE7,
		MAL,
		SPECIAL_CHAR,
		ALPHA
	};

struct TokenizerT_{
	char *words;					// The entire string given by the user
	int currentPos;					// The current position we are at in the string
	enum TokenizerState tstate;			// might not be necessary in the struct
};

//Special characters declaration
const char *special_chars[45][2]={
	{"+","plus"},
	{"-","dash"},
	{".","period"},
	{"*","asterisk"},
	{"/","forward slash"},
	{"!","exclamation"},
	{"@","at"},
	{"#","hash"},
	{"$","dollar"},
	{"%","modulus"},			
	{"^","power"},
	{"[","left brace"},
	{"]","right brace"},
	{"{","left curly brace"},
	{"}","right curly brace"},
	{"(","left round brace"},
	{")","right round brace"},
	{"=","equals"},
	{"_","underscore"},
	{"~","tilde"},
	{":","colon"},
	{";","semicolon"},
	{",","comma"},
	{"<","less than"},
	{">","greater than"},
	{"|","or"},
	{"?","question mark"},
	{"->","structure pointer"},
	{"++","increment"},
	{"--","decrement"},
	{">>","right shift"},
	{"<<","left shift"},
	{"<=","less than equals"},
	{">=","greater than equals"},
	{"==","equals check"},
	{"!=","not equals"},
	{"&&","logical and"},
	{"||","logical or"},
	{"+=","plus equals"},
	{"-=","minus equals"},
	{"*=","star equals"},
	{"/=","divide equals"},
	{"%=","modulus equals"},
	{"&=","and equals"},
	{"|=","or equals"}
};


typedef struct TokenizerT_ TokenizerT;
typedef enum TokenizerState TokenizerState;

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
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
	printf("Creating Tokenizer.. \n");
	TokenizerT  *TObject = (TokenizerT *)malloc(sizeof(TokenizerT));
	TObject->words= (char *)malloc(strlen(ts)*sizeof(char));	//testing this used to be 5
	strcpy(TObject->words, ts);
	printf("Tokenizer created: %s  \n",TObject->words);
	if(TObject!=NULL)
		return TObject;
  return NULL;
}

//function to check for special characters
char * isSpecialChar(char * word){
	int i;
	for(i=0;i<45;++i)
	{
		if(strcmp(special_chars[i][0],word)==0)
		{
			printf("%s \n", special_chars[i][1]);
			return special_chars[i][1];
		}
	}
	return "error";

}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT * tk){
	free(tk->words);
	free(tk);	
}


enum TokenizerState getNextState(char nextchar, enum TokenizerState tstate)
{
	switch(tstate){
		case INIT:
			if(nextchar=='0')
			{
				// printf("%d line\n",__LINE__);
				return TS_STATE0;
			}
			else if(isdigit(nextchar))
			{
				// printf("%d line\n",__LINE__);
				return TS_STATE1;
			}
			// if(nextchar=="")
			// {
			// 								//todo: escape characters!
			// }
			// printf("%d line\n",__LINE__);
			return SPECIAL_CHAR;
		case TS_STATE0:
			if(nextchar=='x' || nextchar=='X')
				return TS_STATE2;
			else if ('0'<=nextchar && nextchar <='7')
				return TS_STATE3;
			else if(nextchar=='.')
				return TS_STATE4;
			else if(isdigit(nextchar))
				return TS_STATE1;
			else
				return MAL;
		case TS_STATE1:
			if(isdigit(nextchar))
				return TS_STATE1;
			else if(nextchar=='.')
				return TS_STATE4;
			else if (nextchar=='e' || nextchar=='E')
				return TS_STATE6;
			else
				return MAL;
		case TS_STATE2:
			if(isxdigit(nextchar))
				return TS_STATE2;
			else
				return MAL;
		case TS_STATE3:
			if('0'<=nextchar && nextchar <='7')
				return TS_STATE3;
			else
				return MAL;
		case TS_STATE4:
			if(isdigit(nextchar))
				return TS_STATE5;
			else
				return MAL;
		case TS_STATE5:
			if(isdigit(nextchar))
				return TS_STATE5;
			else if(nextchar=='e' || nextchar=='E')
				return TS_STATE6;
			else 
				return MAL;
		case TS_STATE6:
			if(isdigit(nextchar))
				return TS_STATE6;
			else if(nextchar=='+'||nextchar=='-')
				return TS_STATE7;
			else
				return MAL;
		case TS_STATE7:
				if(isdigit(nextchar))
					return TS_STATE7;	
				else
					return MAL;
		case SPECIAL_CHAR:
				if(isdigit(nextchar)==0&&isalpha(nextchar)==0)
					return SPECIAL_CHAR;
		case MAL:
			return MAL;
		
			// all possibilities as per the FSM
	}
	return MAL;

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
	//printf("Entered next token \n");
	int i=tk->currentPos;
	
	/*FLAG LOGIC: 
	0- token not started yet, 
	1- token started with alphabets, 
	2- token started with numbers, 
	3-token started but contains special characters, 
	4-token contains a mix of aplha and num
	5-token contains num and special characters nd alpha
	/main flag stores the main flag when we start the token, and current flag stores the flag updated while traversing through the token
	*/
	int firstflag=0;
	int mainflag=0;
	int j=i;

	char *token;
	int wordlength=0; //counts the length of token to be generated
	while(i<strlen(tk->words))
	{
		//printf("current char: %c\n", tk->words[i]); //this outputs spaces as well
		if(isspace((int)tk->words[i])==0)  			//the character is NOT a whitespace, which means token started
		{
			if(isalpha((int)tk->words[i]))
			{
				// printf("%d is line \n", __LINE__);
				if(mainflag==0||mainflag==1)
					mainflag = 1;
				else if(mainflag==2||mainflag==4)
					mainflag = 4;
				else if(mainflag ==5)
					mainflag=5;
				else
				{
					break;
				}

			}
			else if(isdigit((int)tk->words[i]))
			{
				if(mainflag==0||mainflag==2)
					mainflag = 2;
				else if(mainflag==1||mainflag==4)
					mainflag=4;
				else if(mainflag==5)
				{
					mainflag=5;
				}
				else
				{
					break;
				}
			}
			else 									// it is a special character!
			{
				//should continue considering it as a token if only numbers are found and only tokens are found, and only alphanumeric is found
				if(mainflag==0||mainflag==3)
				{
					mainflag=3;
				}
				else if(mainflag==2||mainflag==4)
				{
					mainflag=5;
				}
				else
				{
					break;
					//break!
				}
			}
			
		}
		else if(mainflag!=0)
		{
			tk->currentPos=i;
			//printf("Ending next token \n");
			break;
		}
		else
		{
			++i;
			j=i;
			continue;
		}
		// printf("%d is line where i is about to be increased \n", __LINE__);
		++i;
	}
	// now our token is from j to i excluding i
	int k;
	token = (char *)(malloc(sizeof(char)*(i-j)));
	for(k=0;k<(i-j);++k)
	{
		token[k]=tk->words[j+k];	
	}
	if(mainflag!=0)
	{
		tk->currentPos=i;
		return token;
	}

	
  return 0;
}

/*
 *tokentype identifies what type of token, prints it out onto screen
*/
char *GetTokenType( char *token)
{
	enum TokenizerState tstate;
	tstate=INIT;
	int i=0;
	if(isalpha(token[0]))
	{
		//keep checking incase we come across special characters, if not, return "word". If yes, call getTokenType on new string!
		while(i<strlen(token) && isalnum(token[i]))
			i++;
		if(i==strlen(token))
			return "WORD";
		else
		{
			//GetTokenType(token[i]);
		}		
	}
	for(i=0;i<strlen(token);i++)
	{
		tstate=getNextState(token[i], tstate);
	}
	switch(tstate){
		case INIT:
			return "error";
		case TS_STATE0:
			return "zero";
		case TS_STATE1:
			return "digit";
		case TS_STATE2:
			return "hexadecimal";
		case TS_STATE3:
			return "octal";
		case TS_STATE4:
		case TS_STATE5:
		case TS_STATE6:
		case TS_STATE7:
			return "float";
		case SPECIAL_CHAR:
			return isSpecialChar(token);
		case MAL:
			return "error in input1";
		default:
			return "error in input";
		// and so on?
	}	
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */





int main(int argc, char **argv) {
	printf("Input: %s \n", argv[1]);
	TokenizerT *  TObject = TKCreate(argv[1]);
	TObject->tstate=INIT;
	char *token = TKGetNextToken(TObject);
	while(token!=0)
	{
		//printf("INMAIN: %s \t %s\n", tokens->contents,tokens->tokentype);
		printf("Token is %s \n",token);
		printf("Token type is: %s \n", GetTokenType(token));
		token=TKGetNextToken(TObject);		
	}

	TKDestroy(TObject);	
  	return 0;
}