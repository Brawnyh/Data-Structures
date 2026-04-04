#include "stack.h"

//liste chainee de la pile
typedef struct s_element{
    int value;
    struct s_element* next;
}*Element;

//rep interne du TAD stack

struct s_Stack{
    Element top;
};

Stack * CreateStack(void){
    Stack *s = malloc(sizeof(struct s_Stack));
    if (s == NULL) {
        perror("malloc");
        exit(1);
    }

    s->top = NULL;
    return s;


}

Stack * push(Stack *s,int e){
    Element nouveau =malloc(sizeof(struct s_element));
    nouveau->value=e;
    nouveau->next=s->top;
    s->top=nouveau;
    return s;
}

Stack *pop(Stack *s){
    assert(s->top!=NULL);
    Element tmp= s->top;
    s->top=s->top->next;
    free(tmp);
    return s;
}


bool isEmpty(Stack *s){
    return (s->top==NULL);
}


int top(const Stack *s){
    assert(isEmpty);
    return s->top->value;
}

//no estoy seguro de la destruccion
Stack *DestroyStack(Stack *s){
    assert(!isEmpty);
    while(!isEmpty(s)){
        pop(s);
    }
    free(s);
    return NULL;
}