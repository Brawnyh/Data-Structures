#include "stack.h"
#include <stdlib.h>
#include <stdio.h>


int main(void){
    Stack s=CreateStack();
    for (int i=0;i<10;i++){
        push(s,i);
        printf("%d",i);
    }
    while(!isEmpty(s)){
        pop(s);
    }
    return 0;
}