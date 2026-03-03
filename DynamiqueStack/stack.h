#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct s_Stack Stack;

Stack* CreateStack(void);

Stack *pop(Stack *s);

bool isEmpty(Stack *s);

Stack top(const Stack *s);

