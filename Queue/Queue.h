#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define QueueSize 16
typedef struct s_Queue Queue;


Queue* createQueue(void);
//Queue *DestrotQueue(Queue *q);
Queue * queue_push(Queue *q,int val);
int queue_top(const Queue *q);
Queue* queue_pop(Queue *q);
bool queue_empty(const Queue *q);











#endif