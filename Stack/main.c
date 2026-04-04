#include "stack.h"
#include <stdio.h>

int main(void){
    Stack* s = CreateStack();
    for (int i = 0; i < 10; i++) {
        push(s, i);
    }

    while(!isEmpty(s)){
        printf("%d\n",top(s));
        pop(s);
    }
  

    DestroyStack(s);
    return 0;
}