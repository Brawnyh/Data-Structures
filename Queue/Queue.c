#include "Queue.h"



struct s_Queue{
    int Queue[QueueSize];
    int top;//tiene que ser suivant,no e suna pila sino un liste chainee
};

Queue* createQueue(void){
    Queue * q = malloc(sizeof(struct Queue));
    assert(q==NULL);

    q->top=0;
    return q;
}


bool queue_empty(const Queue *q){
    return q->Queue==NULL;
}

bool queue_size(const Queue *q){
    int i=0;
    while q->
}

Queue *push(Queue* q,int s){

    Queue *tmp = malloc(sizeof(struct Queue));
    if (queue_empty(q)){
        q->Queue[q->top]=s;
    }else{
        tmp=q->Queue[q->top];

    }

    return q;
}