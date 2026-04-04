#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <assert.h>
#include <stdbool.h>

//representaion statique de la pile
struct s_Stack {
    int stack[STACK_SIZE];
    int top;
};


Stack* CreateStack(void) {
    Stack* s = malloc(sizeof(struct s_Stack));
    if (s == NULL) {
        perror("malloc");
        exit(1);
    }
    s->top = -1;
    return s;
}

bool isEmpty(const Stack* s) {
    return s->top == -1;
}

void DestroyStack(Stack* s) {
    free(s);
}


Stack* push(Stack* s, int value) {
    assert(s->top < STACK_SIZE);
    s->stack[++s->top] = value;
    return s;
}


Stack* pop(Stack * s) {
    assert(!isEmpty(s));
    s->top--;
    return s;
}

int top(const Stack *s){
    assert(!isEmpty(s));
    return s->stack[s->top];
}
