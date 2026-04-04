#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define STACK_SIZE 16
typedef struct s_Stack Stack;


Stack* CreateStack(void);
void DestroyStack(Stack* s);
Stack* push(Stack* s, int value);
Stack* pop(Stack* s);
bool isEmpty(const Stack* s);

int top(const Stack *s);
#endif