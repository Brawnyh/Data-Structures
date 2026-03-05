#include "Queue.h"



struct s_Queue{
    int Queue[QueueSize];
    int top;
};

Queue* createQueue(void){
    Queue * q = malloc(sizeof(struct Queue));
    assert(q==NULL);

    q->top=QueueSize-1;
    return q;
}


bool queue_empty(const Queue *q){
    return q->Queue==NULL;
}


Queue *push(Queue* q,int s){
    assert()
    q->Queue[q->top]=s;
    return q;
}