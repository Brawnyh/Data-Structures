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

Queue *shuntingYard(Queue *infix){
	//notation postFix
	//d'abord chiffre apprés symboles
	
	Queue* output=create_queue();
	Token* tok;
	Stack* opStack = create_stack(queue_size(infix)); 

	while (!queue_empty(infix)){
		tok=(Token*) queue_pop(infix); //erreur de type sans le cast
		if (token_is_number(tok)){
			queue_push(output,tok);
		}
		else if (token_is_operator(tok)){
			while (!stack_empty(opStack) && token_is_operator(stack_top(opStack))) {
    			Token* topOp = (Token*) stack_top(opStack);
    			if ((token_operator_priority(topOp) > token_operator_priority(tok)) ||
        			(token_operator_priority(topOp) == token_operator_priority(tok) && token_operator_leftAssociative(tok))) {
        			queue_push(output, (Token*)stack_pop(opStack));
    			} else {
        			break;
    			}
			}				
			stack_push(opStack,tok);
		}
		else if (token_is_left_parenthesis(tok)){
			stack_push(opStack,tok);
		}

		else if (token_is_right_parenthesis(tok)){
			while(!stack_empty(opStack) && !token_is_left_parenthesis(stack_top(opStack))){
				queue_push(output,(Token*)stack_pop(opStack));
			}
			if (!stack_empty(opStack)){
				stack_pop(opStack);
			}
		}
	}

	while(!stack_empty(opStack)){
		Token *t=(Token*) stack_pop(opStack);
		queue_push(output,t);
		
	}
	delete_stack(&opStack);
	return output;
}

float evaluatePostfix(Queue* postfix){
    Stack* stack = create_stack(queue_size(postfix));
    while (!queue_empty(postfix)){
        Token* tok = (Token*) queue_pop(postfix);

        if (token_is_number(tok)){
            stack_push(stack, tok);
        }
        else if (token_is_operator(tok)){
            Token* b = (Token*) stack_pop(stack);
            Token* a = (Token*) stack_pop(stack);

            float v1 = token_value(a);
            float v2 = token_value(b);
            float res = 0;

            switch(token_operator(tok)){
                case '+': res = v1 + v2; break;
                case '-': res = v1 - v2; break;
                case '*': res = v1 * v2; break;
                case '/': res = v1 / v2; break;
                case '^': res = pow(v1, v2); break;
            }
            Token* result = create_token_from_value(res);
            stack_push(stack, result);
        }
    }
    Token* final = (Token*) stack_pop(stack);
    float result = token_value(final);

    delete_stack(&stack);
    return result;
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
	Queue *postfix;
	float res;
	while((nlus=getline(&line,&longeur,input))!=-1){
		//printf("Input: %s\n",nlus);
		if (nlus>1){
			printf("Input: %s",line);
			q=stringToTokenQueue(line);
			printf("Infix: ");
			print_queue(stdout,q);
			printf("\n");

			printf("Postfix: ");
			postfix=shuntingYard(q);
			print_queue(stdout,postfix);
			printf("\n");

			res=evaluatePostfix(postfix);
			printf("Result: %f\n",res);

			delete_queue(&q);
			delete_queue(&postfix);
		}
		
	}
	
	
	free(line);
	
	//fclose(input);
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


