#include "Queue.h"


//chained liste
typedef struct s_internalQueue{
    int value;
    struct s_internalQueue *next;
}internalQueue;

//indices
struct s_Queue{
    struct s_internalQueue *head;
    struct s_internalQueue *tail;
    unsigned int size;
};

Queue* createQueue(void){
    Queue * q = malloc(sizeof(struct s_Queue));
    q->head=NULL;
    q->tail=NULL;
    q->size=0;
    return q;
}

Queue *queue_push(Queue* q,int s){
    internalQueue **insert_at=(q->size ? &(q->tail->next): &(q->head));//si es el primer valor o no
    internalQueue *tmp=malloc(sizeof(internalQueue));
    tmp->value=s;
    tmp->next=NULL;
    *insert_at=tmp;
    q->tail=tmp;
    ++q->size;
    return q;
}


bool queue_empty(const Queue *q){
    return (q->size==0);
}




Queue* queue_pop(Queue *q){
    assert(!queue_empty(q));
    internalQueue *old =q->head;
    q->head=q->head->next;
    q->size--;
    free(old);
    return q;
}

int top(Queue* q){
    assert(!queue_empty(q));
    return q->head->value;
}
