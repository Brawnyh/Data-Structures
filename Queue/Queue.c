#include "Queue.h"



struct s_Queue{
    int Queue[QueueSize];
    int head;
    int tail;
    unsigned int size;
  

};

Queue* createQueue(void){
    Queue * q = malloc(sizeof(struct Queue));
    assert(q==NULL);
    q->head=0;
    q->tail=-1;
    q->size=0
    return q;
}


bool queue_empty(const Queue *q){
    return (q->Queue==NULL);
}

bool queue_size(const Queue *q){
    int i=0;
    
}

Queue *push(Queue* q,int s){
    assert(q->size<QueueSize);
    q->tail=(q->tail + 1)%QueueSize;//el modulo no hace nada hasta que detecta que tail es 16 y asi envia 0(primer elemento)(circular)
    q->Queue[q->tail]=s;
    ++q->size;
    return q;
}

int top(Queue* q){
    assert(!queue_empty(q));
    return q->Queue[q->head];
}



Queue