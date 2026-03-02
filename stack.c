#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <assert.h>
#include <stdbool.h>




void CreateStack(Stack* s) {
    Stack* s = malloc(sizeof(Stack));
    if (s == NULL) {
        perror("malloc");
        exit(1);
    }
    s->top = -1;
    return s;
}

bool isEmpty(Stack* s) {
    return s->top == -1;
}

void DestroyStack(Stack* s) {
    free(s);
}


void push(Stack* s, int value) {
    assert(s->top < STACK_SIZE);
    s->stack[++s->top] = value;
}


void pop(Stack * s) {
    assert(!isEmpty(s));
    s->top--;
}

int top(Stack *s){
    assert(!isEmpty(s));
    return s->stack[s->top];
}
