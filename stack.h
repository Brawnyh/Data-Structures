#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <assert.h>
#include <stdbool.h>

#define STACK_SIZE 16
typedef struct{
    int stack[STACK_SIZE];
    int top;
}Stack;


void CreateStack(Stack *s);
void DestroyStack(Stack* s);
void push(Stack* s, int value);
void pop(Stack* s);
bool isEmpty(const Stack* s);

int top(const Stack *s);
#endif