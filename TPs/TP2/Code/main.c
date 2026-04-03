// Need this to use the getline C function on Linux. Works without this on MacOs. Not tested on Windows.
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "token.h"
#include "queue.h"
#include "stack.h"


/** 
 * Utilities function to print the token queues
 */
void print_token(const void* e, void* user_param);
void print_queue(FILE* f, Queue* q);


bool isSymbol(char c){
	if (c=='+' || c== '-' || c=='/' || c=='*' || c== '^' || c== ')' || c== '('){
		return true;
	}else{
		return false;
	}
}

Queue *stringToTokenQueue(const char * expression){
	Queue* q=create_queue();
	const char*curpos=expression;
	//int i=0;
	//int tmpIndex=0;
	//char tmp[128];
	while(*curpos!='\0'){
		while (*curpos == ' ' || *curpos =='\n'){
			curpos++;
		}
		if (*curpos=='\0') break;

		if (isSymbol(*curpos)){
			Token *tok=create_token_from_string(curpos,1);
			queue_push(q,tok);
			curpos++;
			
		}else{
			const char *debut=curpos;
			int longueur=0;
			while(*curpos !='\0' && !isSymbol(*curpos) && *curpos != ' ' && *curpos != '\n'){
				curpos++;
				longueur++;
			}
			Token *tok =create_token_from_string(debut,longueur);
			queue_push(q,tok);
		}
		

	}
	
	return q;
}


/** 
 * Function to be written by students
 */
void computeExpressions(FILE* input) {
	(void)input;
	char *line=NULL;
	size_t longeur=0;
	ssize_t nlus;
	Queue *q;
	while((nlus=getline(&line,&longeur,input))!=-1){
		//printf("Input: %s\n",nlus);
		if (nlus>1){
			printf("Input: %s",line);
			printf("Infix: ");
			q=stringToTokenQueue(line);
			print_queue(stdout,q);
			printf("\n");
		}
		
	}
	
	delete_queue(&q);
	free(line);
	
	//fclose(input);
}


Queue *shuntingYard(Queue *infix){
	//notation postFix
	//d'abord chiffre apprés symboles
	
	Queue* output=create_queue();
	const Token* tok;
	while (!queue_empty(infix)){
		tok=queue_top(infix);
		if (token_is_number(tok)){
			queue_push(output,tok);
		}
		if (token_is_operator(tok)){
			while(token_operator_priority(queue_top(infix))>token_operator_priority(tok) ||
			 token_operator_priority(queue(infix))==token_operator_priority(tok) && token_operator_leftAssociative(tok) &&
			token_is_parenthesis(queue_top(infix))!=create_token_from_string(")")) {//conditions a verifier
				queue_push(output,queue_pop(infix));
				//push the read operator onto the operator stack?
			}
			queue(push)

		}

		if (token == ")")
	}
}

/** Main function for testing.
 * The main function expects one parameter that is the file where expressions to translate are
 * to be read.
 *
 * This file must contain a valid expression on each line
 *
 */
int main(int argc, char** argv){
	if (argc<2) {
		fprintf(stderr,"usage : %s filename\n", argv[0]);
		return 1;
	}
	
	FILE* input = fopen(argv[1], "r");

	if ( !input ) {
		perror(argv[1]);
		return 1;
	}

	computeExpressions(input);

	fclose(input);
	return 0;
}
 
void print_token(const void* e, void* user_param) {
	FILE* f = (FILE*)user_param;
	Token* t = (Token*)e;
	token_dump(f, t);
	
}

void print_queue(FILE* f, Queue* q) {
	fprintf(f, "(%d) --  ", queue_size(q));
	queue_map(q, print_token, f);
}


