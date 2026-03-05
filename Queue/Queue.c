#include "Queue.h"



struct s_Queue{
    int Queue[QueueSize];
    int top;
};

Queue* createQueue(void){
    Queue * q = malloc(sizeof(struct Queue));
    assert(q==NULL);

    q->top=NULL;
    return q;
}