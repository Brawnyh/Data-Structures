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

/** 
 * Function to be written by students
 */
void computeExpressions(FILE* input) {
	(void)input;
	//input=fopen((char *)input,"r"); tal vez no e snecesario abrirlo aqui
	//if (input==0){perror("erreur d'ouverture");exit(1);}
	char *line=malloc(sizeof(char));
	//if (line==NULL){perror("erreur d'allocation");exit(1);}
	char buffer[1024];
	//on stock le nb de ligne du fichier(exemple dans man)
	//ssize_t nlus;
	size_t longeur;
	ssize_t nlus=getline(&line,&longeur,input);
	while (nlus!=0){
		fread(buffer,longeur,1,input);
		printf("Input: %s\n",buffer);
		nlus--;
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
